#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20 /*max num simultaneously opened files */


typedef struct _iobuf {
    int cnt; /* number of rest symbols */
    char *ptr; /* current symbol position */
    char *base; /* buffer address */
    int flag; /* access mode */
    int fd; /* file descriptor */
} FILE;

extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

enum _flags {
    _READ =01, /* file is opened for reading */
    _WRITE = 02, /* file if opened for writing */
    _UNBUF = 04, /* not bufferizing */
    _EOF = 010, /* file has met EOF */
    _ERR = 020 /* file find an error */
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferrro(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)
#define getc(p) (--(p)->cnt >= 0 \
		 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))

#define putc(x,p) (--(p)->cnt >=0 \
		   ?  *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

