#include "lib/cmdArgs.h"
#include "lib/session.h"
#include "lib/server.h"

#include <iostream>

int main(int argc, char** argv)
{
    Parametres cmd(argc, argv);
    pid_t pid = fork();
    if( !pid) {
	umask(0);
	setsid();
	chdir(cmd.getDir().c_str());
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	boost::asio::io_service io_service;
	server s(io_service, cmd.getIP(), cmd.getPort());
	io_service.run();
    }
    else {
	std::cout << pid <<std::endl;
	return 0;
    }
    
    return 0;
}
