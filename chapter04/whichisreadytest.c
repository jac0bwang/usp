#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 1000

int whichisready(int fd1, int fd2);

int main(void) {

   int fd;
   int readyfd;
   char buf[BUFSIZE];
   int bytes;

   fd = open("inpipe",O_RDONLY);
   if (fd < 0) {
      fprintf(stderr,"Error opening inpipe\n");
      return 1;
   }
   fprintf(stderr,"Starting to read from inpipe and standard input\n");

   for ( ; ; ) {
      readyfd = whichisready(fd,STDIN_FILENO);
      if (readyfd < 0) {
         fprintf(stderr,"which_is_ready error\n");
         return 1;
      }
      bytes = read(readyfd,buf,BUFSIZE);
      if (bytes < 0) {
         fprintf(stderr,"Error readying from %d\n",readyfd);
         return 1;
      }
      if (bytes == 0) {
         fprintf(stderr,"Close on %d\n",readyfd);
         return 0;
      }
      fprintf(stderr,"Got from %d:%.*s\n",readyfd,bytes,buf);
   }
}
