#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int isSpace(char s) {
    if (s == ' ' || s == '\t' || s == '\r') return 1;
    return 0;
}
void parseIntoCommands(const char* str, size_t n, char (*c)[80]) {
    int i =0;
    int j = 0;
    int k = 0;
    int len = strlen(str);
    if (str[len-1] == '\n') len -=1;
    for( i = 0; i < len; ++ i) {
	if (str[i] != '|') {
	    c[j][k++] = str[i];		
	}			       
	else {
	    c[j][k] = '\0';
	    j++;
	    k = 0;
	}
    }
    c[j][k] = '\0';
}

int calcPipes( const char* str) {
    int i = 0;
    int pipes = 0;
    while( str[i] ) {
	if(str[i] == '|') pipes++;
	i++;
    }
    return pipes;
}
int countWords(const char* str) {
    int i,c = 0;
    int len = strlen(str);
    char prev = ' ';
    for(i = 0; i < len; ++i) {
	if( isSpace(prev) && !isSpace(str[i]) ) c++;
	prev = str[i];	    
    }
    return c;
}

void parseCommandToParams(const char* str, size_t n, char *c[] ) {
    int i = 0, j = 0, k = 0;
    int len = strlen(str);
    c[j] =(char*) calloc( sizeof(char), 80);
    
    for(; i < len && isSpace(str[i]); ++i);
    

    while (i < len) {
	if ( !isSpace(str[i]) )
	    c[j][k++] = str[i++];	
	else {
	    c[j][k] = '\0';
	    for(; i < len && isSpace(str[i]); ++i);
	    if(i < len) {
		j++;
		c[j] =(char*) calloc( sizeof(char), 80);
	    }
	    k = 0;

	}
    }

    c[j+1] = NULL;
}

void freeArgs(char **c, size_t n) {
    for(; n > 0; --n) free(c[n-1]);
}

void PrintCom(char *c[], int n) {
    int i = 0;
    for( i = 0; i < n; ++i) 
	if (c[i] != NULL)
	    printf("c: %s\n", c[i]);
}


void exe(char (*c)[80], int i) {
    int nc = countWords(c[i]) + 1;
    char *w[nc];
    parseCommandToParams(c[i], nc, w) ;
    execvp(w[0], w);
}

void writeResultToFile(int fd[]) {
    const char *path = "/home/box/result.out";
    int file = open(path, O_CREAT | O_WRONLY,S_IRUSR);
    //  --> [fd(1)---pipe---fd(0)] --> file
    int n;
    char buf[1024];
    while ( n = read(fd[0], buf, 1024))  {
	write(file, buf, n);
    }
    close(file);

}

int ExecuteCommands(char (*c)[80], int n, int i, int ifd[] /*input pipe*/)
{
    int fd[2];
    pipe(fd);
    if( i < n -1) {
	pid_t pid = fork();
	if( pid == -1) {
	    perror("fork error\n");
	    exit(1);
	}
	if(pid) {
	    //parent
	    close(fd[1]);
	    ExecuteCommands(c, n, ++i, fd);
	}
	else {
	    //child
	    if(i > 0){
		close(STDIN_FILENO);
		dup2(ifd[0], STDIN_FILENO);
		close(ifd[0]); close(ifd[1]);
	    }
	    close(STDOUT_FILENO);
	    dup2(fd[1], STDOUT_FILENO);
	    close(fd[0]); close(fd[1]);
	    exe(c, i);
	}
    }  
    else if (i == n - 1){
	pid_t pid = fork();
	if(pid){
	    close(fd[1]);
	    writeResultToFile(fd);
	}
	if(!pid){
	    close(STDIN_FILENO);
	    dup2(ifd[0], STDIN_FILENO);
	    close(STDOUT_FILENO);
	    dup2(fd[1], STDOUT_FILENO);
	   
	    close(ifd[0]); close(ifd[1]);
	    exe(c,i);
	}
    }
    
    
}


int main()
{
    char input[256];
    fgets(input, 256, stdin);
    int ncommands = calcPipes(input) + 1;

    char c[ncommands][80];
    parseIntoCommands(input, ncommands, c);

    int fd[2];
    ExecuteCommands(c, ncommands, 0, fd);
    //    wait(NULL);
    return 0;
}
