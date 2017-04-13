#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <fstream>
#include <vector>

#include "boost/asio.hpp"

using boost::asio::ip::tcp;

class session {
    /* http session */
private:
    tcp::socket socket_;
    enum { max_length = 4024 };
    char data_[max_length];
    std::ofstream *log_;
protected:
    bool parseRequest(std::string request, std::vector<std::string> &params);
    
public:
    session(boost::asio::io_service &io_service):
	socket_(io_service)
    {}
    session(boost::asio::io_service &io_service, std::ofstream* log):
	socket_(io_service),
	log_(log)
	{}
    
    ~session();
    void send(const char* str, size_t len);
    void SendError(int n);
    tcp::socket &socket() { return socket_;}
    void start(); // start session, initial function

    
    void handle_read(const boost::system::error_code &error,
		     size_t bytes_tansferred);


    void handle_write(const boost::system::error_code &error);


};


#endif /* SESSION_H */
