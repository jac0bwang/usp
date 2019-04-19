#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void monitorpoll(int fd[], int numfds);

void docommand(char *buf, int num) {
   fprintf(stderr,"Got command !%.*s!\n",num,buf);
}

int main(int argc, char *argv[]){
   int *fds;
   int i;

   if (argc <= 1) {
       fprintf(stderr,"Usage: %s pipe1 pipe2 ...\n",argv[0]);
       return 1;
   }
   fds = (int *)malloc((argc-1)*sizeof(int));
   if (fds == NULL) {
       fprintf(stderr,"Malloc error\n");
       return 1;
   }
   for (i=0;i<argc-1;i++) {
      fds[i] = open(argv[i+1],O_RDONLY);
      if (fds[i] == -1) {
         fprintf(stderr,"Error opening %s for read\n",argv[i+1]);
         return 1;
      }
   }
   monitorpoll(fds,argc-1);
   return 0;
}
