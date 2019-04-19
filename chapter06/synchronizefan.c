#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "restart.h"

int main  (int argc, char *argv[]) {
   char buf[] = "g"; 
   pid_t childpid = 0;
   int fd[2]; 
   int i, n;

   if (argc != 2){      /* check for valid number of command-line arguments */
      fprintf (stderr, "Usage: %s processes\n", argv[0]);
      return 1;
   }
   n = atoi(argv[1]);
   if (pipe(fd) == -1) {                 /* create pipe for synchronization */
      perror("Failed to create the synchronization pipe");
      return 1;
   }
   for (i = 1; i < n;  i++)                  /* parent creates all children */
       if ((childpid = fork()) <= 0)
           break;
   if (childpid > 0) {          /* write synchronization characters to pipe */
      for (i = 0; i < n; i++)
         if (r_write(fd[1], buf, 1) != 1)
            perror("Failed to write synchronization characters");
   }
   if (r_read(fd[0], buf, 1) != 1)                      /* synchronize here */
      perror("Failed to read synchronization characters");
   fprintf(stderr, "i:%d  process ID:%ld  parent ID:%ld  child ID:%ld\n",
           i, (long)getpid(), (long)getppid(), (long)childpid);
   return (childpid == -1);
}
