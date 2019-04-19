#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "restart.h"
#define BUFSIZE 1024

int main(int argc, char *argv[]) {
   char buffer[BUFSIZE];
   char *c;
   pid_t childpid = 0;
   int delay;
   volatile int dummy = 0;
   int i, n;

   if (argc != 3){   /* check for valid number of command-line arguments */
      fprintf (stderr, "Usage: %s processes delay\n", argv[0]);
      return 1;
   }
   n = atoi(argv[1]);
   delay = atoi(argv[2]);
   for (i = 1; i < n; i++)
      if (childpid = fork())
         break;
   snprintf(buffer, BUFSIZE,
       "i:%d  process ID:%ld  parent ID:%ld  child ID:%ld\n",
       i, (long)getpid(), (long)getppid(), (long)childpid);
 
    c = buffer;
   /********************** start of critical section **********************/
   while (*c != '\0') {
      fputc(*c, stderr);
      c++;
      for (i = 0; i < delay; i++) 
         dummy++;
   }
   /********************** end of critical section ************************/
   if (r_wait(NULL) == -1)
      return 1;
   return 0;
}
