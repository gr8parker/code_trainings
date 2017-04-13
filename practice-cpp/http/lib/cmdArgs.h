#ifndef CMDARGS_H
#define CMDARGS_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

class Parametres {
    /*TODO check validity of input data*/
public:
    Parametres(int argc, char** argv) {
	int opt;
	while( ((opt = getopt(argc, argv, "h:p:d:")) != -1) ) {
	    switch (opt) {
	    case 'h':
		ip = optarg;
		break;
	    case 'p':
		port = atoi(optarg);
		break;
	    case 'd':
		dir = optarg;
		break;
	    default:
		usage_msg(argv[0]);
	    }
	}
    }
    
    void usage_msg(const char* name) {
	    fprintf(stderr, "Usage %s [-h <ip>] [-n <port>] [-d <directory>]\n",
		    name);
	    exit(EXIT_FAILURE);
    }
    
    std::string getIP() { return ip; }
    int getPort() { return port; }
    std::string getDir(){ return dir;}
private:
    std::string ip, dir;
    int port;
};

#endif /* CMDARGS_H */
