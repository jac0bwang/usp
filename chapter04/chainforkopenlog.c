#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "atomic_logger.h"

#define BUFSIZE 1024

int main  (int argc, char *argv[]) {
   char buf[BUFSIZE];
   pid_t childpid = 0; 
   int i, n;
 
   if (argc != 3){       /* check for valid number of command-line arguments */
      fprintf (stderr, "Usage: %s processes filename\n", argv[0]);
      return 1;
   }     
   n = atoi(argv[1]);                              /* create a process chain */
   for (i = 1; i < n; i++)
       if (childpid = fork())
          break;
   if (childpid == -1) {
      perror("Failed to fork");
      return 1;
   }     

   if (atomic_log_open(argv[2]) == -1) {             /* open atomic log file */
      fprintf(stderr, "Failed to open log file");
      return 1;
   }
                                /* log the output, using two different forms */
   sprintf(buf, "i:%d process:%ld", i, (long)getpid());
   atomic_log_array(buf, strlen(buf));
   sprintf(buf, " parent:%ld child:%ld\n", (long)getppid(), (long)childpid);
   atomic_log_string(buf);
   if (atomic_log_send() == -1) {
      fprintf(stderr, "Failed to send to log file");
      return 1;
   }
   atomic_log_close();
   return 0;
}
