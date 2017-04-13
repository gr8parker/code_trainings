#include "session.h"

#include "boost/bind.hpp"
#include "boost/system/error_code.hpp"
#include "Time.h"
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

bool session::parseRequest(std::string request, std::vector<std::string> &params) {
    // separate the 3 main parts and
    // return vector of params: protocol, method, url, url_par1,  url_par2, ...
    std::istringstream iss(request);

    std::string method;
    std::string query;
    std::string protocol;

    if( !(iss >> method >> query >> protocol)) {
	std::cout << "ERROR: parsing request\n";
	return false;
    }

    iss.clear();
    iss.str(query);

    std::string url;
    if( !std::getline(iss, url, '?')) { //remove the URL part
	std::cout << "ERROR: parsing request url\n";
	return false;
    }
    std::string urlpars;
    iss >> urlpars;
    params.push_back(protocol);
    params.push_back(method);
    if (url[0] == '/') {
	int i = 0;
	while(url[i++] == '/')
	    ;
	url = std::string(url.begin()+i-1, url.end());
    }
    params.push_back(url);
    params.push_back(urlpars);
    // let's skip parameters separating into key=value
    return true;
}

void session::start() {
    if(log_->is_open()) {
	(*log_) << getCurrentTime() << ": "
		<< socket_.remote_endpoint().address().to_string()
		<<" connection is opened" <<std::endl;
    }
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
			    boost::bind(&session::handle_read,
					this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred
					));
};

void session::send(const char* str, size_t len) {
    boost::asio::async_write(socket_,
			     boost::asio::buffer(str, len),
			     boost::bind(&session::handle_write,
					 this,
					 boost::asio::placeholders::error)
			     );
	
}

void session::handle_read(const boost::system::error_code &error,
		 size_t bytes_tansferred) {
    if( !error) {
	// Формируем запрос из полученных данных
	std::string request = data_;
	// Запрос должн обрываться  последовательностью \r\n\r\n
	// Не рассмотриваем тут получение POST запроса
	// А GET не должен привышать 4 килобайта

	// Парсим запрос с помощью регулярных выражений
	std::vector<std::string> request_params;
	    
	if( !parseRequest(request, request_params) ) {
	    SendError(400);
	    return;
	}
	std::string file = request_params.at(2);
	std::cout <<"GET file: " << file << std::endl;
	//	std::cout << "GET file:" << file <<std::endl;
	// Проверяем существует ли файл
	FILE *fptr = fopen(file.c_str(), "r");
	if( fptr == NULL ) {
	    SendError(404);
	    return;
	}
	fclose(fptr);
	// получаем тип файла по расширению
	std::string file_type( file.begin()+file.rfind('.')+1, file.end() );
	std::cout << "File type request: " << file_type <<std::endl;

	std::string ContentType = "";
	if( file_type == "jpeg") {
	    ContentType = "image/jpeg";
	} else if (file_type == "html") {
	    ContentType = "text/html";
	} else 	if( file_type == "jpeg") {
	    ContentType = "image/png";
	}else{
	    ContentType ="application/unknown";
	}
	
	std::ifstream input(file.c_str(), std::ios::binary);

	std::vector<char> content;
	std::copy(std::istreambuf_iterator<char>(input),
		  std::istreambuf_iterator<char>(),
		  std::back_inserter(content) );
	size_t ContentLength = content.size() * sizeof(char);
	
	// Посылаем заголовки
	std::string headers = std::string("HTTP/1.0 200 OK\nContent-Type: ") +
	    ContentType + std::string("\nContent-Length: ") +
	    std::to_string(ContentLength) +"\n\n";

	send(headers.c_str(), headers.length());
	for(int i = 0; i < content.size(); ++i) {
	    send(&content[i], sizeof(char));
	}
	input.close();

	std::string enter ="\n";
	send(enter.c_str(), enter.length());
	
	
	delete this;			     

    } else {
	delete this;
    }
}

void session::handle_write(const boost::system::error_code &error) {
    if (error) delete this;
}

void session::SendError(int n) {
    boost::system::error_code err;
    err = boost::system::errc::make_error_code(boost::system::errc::bad_message);
    std::string html = std::string("<html><body><h1>")
	+ std::to_string(n) + "</h1></body></html>";
    std::string msg = "HTTP/1.0 ";
    if (n == 400) {
	msg += "400 Bad Request\n";
    }
    if (n == 404) {
	msg += "404 Not Found\n";
    }
    msg+="\nContent-type: text/html\nContent-length: " + std::to_string(html.length()) + "\n\n" ;
    msg+=html;
    boost::asio::async_write(socket_,
			     boost::asio::buffer(msg, msg.length()),
			     boost::bind(&session::handle_write,
					 this,
					 err)
			     );

}


session::~session() {
    if(log_->is_open()) {
	(*log_) << getCurrentTime()  << ": "
		<< socket_.remote_endpoint().address().to_string()
		<<" connection is closed" <<std::endl;
    }
}
