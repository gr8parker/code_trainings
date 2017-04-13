#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


struct message {
	long mtype;
	char mtext[80];
};

int main() 
{
	key_t key = ftok("/tmp/msg.temp", 1);

	int qid = msgget(key, IPC_CREAT | IPC_EXCL | 0777);
	
	int nbytes;
	struct message msg;
	nbytes = msgrcv(qid, &msg, 80,0, 0);

	const char *out_pwd =  "/home/box/message.txt";
	int fd = open(out_pwd, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if( fd == -1 ) {
		perror(" Open error\n");
		return -1;
	}
	write(fd, msg.mtext, nbytes);
	close(fd);

	msgctl(qid, IPC_RMID, NULL);

	return 0;
}
