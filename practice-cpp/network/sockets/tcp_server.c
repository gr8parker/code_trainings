/* screen */
#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char ** argv) {
    //1.
    int MasterSocket = socket( AF_INET /*IPv4*/,
			       SOCK_STREAM  /*TCP */,
			       IPPROTO_TCP);
    struct sockaddr_in SockAddr;
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_port = htons(12345);
    SockAddr.sin_addr.s_addr = htonl(INADDR_ANY); //0.0.0.0
    bind(MasterSocket, (struct sockaddr *)(&SockAddr), sizeof(SockAddr));
    
    listen(MasterSocket, SOMAXCONN);
    //2
    while(1) {
/*	int SlaveSocket = accept(MasterSocket, 0, 0);

	int Buffer[5] = {0, 0, 0, 0, 0};
	recv(SlaveSocket, Buffer, 4, MSG_NOSIGNAL);
	send(SlaveSocket, Buffer, 4, MSG_NOSIGNAL);
	
	shutdown(SlaveSocket, SHUT_RDWR);
	close(SlaveSocket);
	printf("%s\n", Buffer);	    */
    }
			       
			      

    return 0;
}

/*
1.
 Как определить что программа работает верно? 
   Для этого отследим системные вызовы, которые происходят:
   strace ./server 2>server.log 
   strace вывовит в стандартный поток ошибок.
   видим системные вызовы по созданию сокетов.
telnet:
   telnet 127.0.0.1 12345
2. Можно отследить через strace ./server
   Видим что создается сокет, потом висит на accept
   Так как вызов у нас блокирующий, то пока не получит 4 байта, не 
   переgстанет висеть
   ps aux | fgrep server
   lsof -p PID  - увидим список дескрипторов на данном сервере
   Если запустим сервер и подсоединимся, то увидим что создался еще один
   сокет и у него появился дескриптор.
   strace -p PID --можно подключиться к процессу и увидеть что он висит на accept
   ltrace   -- вызовы из сторонних библиотек
*/
