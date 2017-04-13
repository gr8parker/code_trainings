#include <stdio.h>
#define MAXLINE 1000

int Getline(char line[], int max);
int strindex(char source[], char searchfor[]);

char pattern[] = "old";

/* find all string that includes patter */
int main()
{
    char line[MAXLINE];
    int found = 0;
    while (Getline(line, MAXLINE) > 0 ) {
	if(strindex(line, pattern) >= 0) {
	    printf("%s\n", line);
	    found++;
	}
    }
	return found;
}

/* getline: read line to line, returns number of characters */
int Getline(char s[], int lim) {
    char c;
    int i = 0;
    while(--lim >0 && (c = getchar()) != EOF && c != '\n')
	s[i++] = c;
    s[i] = '\0';
    return i;    
}
/* strindex: find an index of startin t at s, return -1 if is not found */
int strindex(char s[], char t[]) {
    int i, j, k;
    for( i = 0; s[i] != '\0'; ++i) {
	for(j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++);
	if (k > 0 && t[k] == '\0') return i;
    }
    return -1;
}
