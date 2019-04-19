#include <stdio.h>
#include <unistd.h>

#define BUFSIZE 1024

int setblock(int fd);
int setnonblock(int fd);

int main(void) {
   char buf[BUFSIZE];
   int n;

   for ( ; ; ) {
      fprintf(stderr,"Blocking input on standard input\n");
      setblock(STDIN_FILENO);
      n = read(STDIN_FILENO,buf,BUFSIZE);
      if (n == 0)
         break;
      if (n > 0)
         fprintf(stderr,"Got %d bytes: %.*s\n",n,n,buf);
      else
         perror("nonblocking error");
      fprintf(stderr,"Nonblocking input on standard input\n");
      n = 0;
      setnonblock(STDIN_FILENO);
      while (n <= 0) {
         n = read(STDIN_FILENO,buf,BUFSIZE);
         if (n > 0)
            fprintf(stderr,"Got %d bytes: %.*s\n",n,n,buf);
         else
            perror("blocking error");
         sleep(1);
      }
   }
   return 0;
} 
