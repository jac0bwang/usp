#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "atomic_logger.h"

#define BUFSIZE 1024

int main  (int argc, char *argv[])
{
   int     i;
   pid_t   childpid;               /* process ID of the forked child  */
   int     n;               /* total number of processes in the chain */
 
   if (argc != 3){ /* check for valid number of command-line arguments */
      fprintf (stderr, "Usage: %s processes filename\n", argv[0]);
      return 1;
   }     
   n = atoi(argv[1]);
     
   childpid = 0;
   for (i = 1; i < n;  ++i)
       if (childpid = fork())
          break;
   if (childpid == -1) {
      perror("The fork failed");
      return 1;
   }     

   if (atomic_log_open(argv[2]) < 0) {
      fprintf(stderr, "Open log file failed");
      return 1;
   }

   atomic_log_printf("i:%d process ID:%ld",i,(long)getpid());
   atomic_log_printf(" parent ID:%ld  child ID:%ld\n",
                      (long)getppid(),(long)childpid);
   if (atomic_log_send() < 0) {
      fprintf(stderr, "Send to log file failed");
      return 1;
   }
   atomic_log_close();
   return 0;
}
