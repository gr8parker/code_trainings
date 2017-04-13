#include "server.h"
#include <boost/bind.hpp>

server::server(boost::asio::io_service &io_service,std::string ip, int port):
    io_service_(io_service),
    ip_( boost::asio::ip::address::from_string(ip)),
    acceptor_(io_service, tcp::endpoint( boost::asio::ip::address::from_string(ip), port) )
{
    
    logfile.open("/tmp/httpserver.log", std::ofstream::out | std::ofstream::app);
    logfile << getCurrentTime() << ": "
	    << " Starting HTTP server" <<std::endl;
	
    session *new_session = new session(io_service_, &logfile);
    acceptor_.async_accept(new_session->socket(),
			   boost::bind(&server::handle_accept,
				       this,
				       new_session,
				       boost::asio::placeholders::error)
			   );
}

void server::handle_accept(session *new_session,
			   const boost::system::error_code& error) {
    if( !error)  {

	std::thread f([new_session](){new_session->start();});
	f.detach();

	new_session = new session(io_service_, &logfile);
	acceptor_.async_accept(new_session->socket(),
			       boost::bind(&server::handle_accept,
					   this,
					   new_session,
					   boost::asio::placeholders::error)
			       );
	    
	    
    } else {
	delete new_session;
    }
}
