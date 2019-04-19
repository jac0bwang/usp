#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void monitorfd(int fd[], int numfds);

void docommand(char *buf, int len) {
   fprintf(stderr,"Got %.*s",len,buf);
}

int main(int argc, char *argv[]) {
   int fd[2];

   if (argc != 3) {
      fprintf(stderr,"Usage: %s file1 file2\n",argv[0]);
      return 1;
   }
   if ( (fd[0] = open(argv[1],O_RDONLY)) < 0) {
      fprintf(stderr,"Error opening file %s\n",argv[1]);
      return 1;
   }
   if ( (fd[1] = open(argv[2],O_RDONLY)) < 0) {
      fprintf(stderr,"Error opening file %s\n",argv[2]);
      return 1;
   }
   monitorfd(fd,2);
   return 0;
}

