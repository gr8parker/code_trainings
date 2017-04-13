#include <ctype.h>
#include <stdio.h>

/* atof: string to float */
double  my_atof(char s[]) {
    double n = 0;
    int i;
    for (i = 0; s[i] ==' ' || s[i] == '\t'; ++i);
    for (; s[i] != '.' && s[i] != '\0'; ++i) {
	int k  = s[i] - '0';
	n = n * 10 + k;
    }
    float dec = 1;
    if (s[i] == '.') i++;
    for(i; s[i] >= '0' && s[i] <='9'; ++i) {
	n = n * 10 + (s[i] -'0');
	dec *= 10;
    }
    return n / dec;    
}

int main() {
    char str[] = "321.12312312";
    double  a = my_atof(str);
    printf("%f\n", a);
};
