int getbytes(void);
int getdone(void);
int geterror(void);
int initsignal(int signo);
int initread(int fdread, int fdwrite, int signo, char *buf, int bufsize);
int suspenduntilmaybeready(void);
