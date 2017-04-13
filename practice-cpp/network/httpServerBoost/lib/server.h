#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>

#include "boost/asio.hpp"

#include "Time.h" // getCurrentTime
#include "session.h"

using boost::asio::ip::tcp;

class server {
private:
    boost::asio::io_service &io_service_;
    tcp::acceptor acceptor_;
    boost::asio::ip::address ip_;
    std::ofstream logfile;
    std::vector<std::thread> threads;

public:
    server(boost::asio::io_service &io_service, std::string ip, int port);
	
    void handle_accept(session *new_session,
		       const boost::system::error_code& error);
    
    ~server() {
	logfile << getCurrentTime() << ": " << "Closing HTTP server" <<std::endl;
	logfile.close();
    }
  
};

    

#endif /* SERVER_H */
