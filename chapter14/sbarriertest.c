#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#define BUFSIZE 1024

int initbarrier(int n);
int waitbarrier(void);

int main(int argc, char *argv[]) {
   int i;
   int n;

   if (argc != 2){   /* check for valid number of command line arguments */
      fprintf (stderr, "Usage: %s processes\n", argv[0]);
      return 1;
   }
   n = atoi(argv[1]);
   if (initbarrier(n) == -1) {
      perror("barrier init");
      return 1;
   }
   for (i = 1; i < n; ++i)
      if (fork())
         break;
   fprintf(stderr,"This is the first message of process %ld\n",(long)getpid());
   if (waitbarrier() == -1) {
      perror("barrier wait");
      return 1;
   }
   fprintf(stderr,"This is the second message of process %ld\n",(long)getpid());
   return 0;
}
