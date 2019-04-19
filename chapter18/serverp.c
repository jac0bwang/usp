#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "restart.h"
#include "uici.h"

int main(int argc, char *argv[]) {
   int bytescopied;
   pid_t child;
   char client[MAX_CANON];
   int communfd;
   int listenfd;
   u_port_t portnumber;
 
   if (argc != 2) {
      fprintf(stderr, "Usage: %s port\n", argv[0]);
      return 1;   
   }  
   portnumber = (u_port_t) atoi(argv[1]);
   if ((listenfd = u_open(portnumber)) == -1) {
      perror("Failed to create listening endpoint");
      return 1;
   }
   fprintf(stderr, "[%ld]: Waiting for connection on port %d\n",
                    (long)getpid(), (int)portnumber);
   for ( ; ; ) {
      if ((communfd = u_accept(listenfd, client, MAX_CANON)) == -1) {
         perror("Failed to accept connection");
         continue;
      }
      fprintf(stderr, "[%ld]:connected to %s\n", (long)getpid(), client);
      if ((child = fork()) == -1) 
         perror("Failed to fork a child");
      if (child == 0) {                                         /* child code */
         if (r_close(listenfd) == -1) {
            fprintf(stderr, "[%ld]:failed to close listenfd: %s\n",
                             (long)getpid(), strerror(errno));
            return 1;
         }
         bytescopied = copyfile(communfd, STDOUT_FILENO);
         fprintf(stderr, "[%ld]:received %d bytes\n",
                          (long)getpid(), bytescopied);
         return 0;
      }
      if (r_close(communfd) == -1)                             /* parent code */
         fprintf(stderr, "[%ld]:failed to close communfd: %s\n",
                          (long)getpid(), strerror(errno));
      while (r_waitpid(-1, NULL, WNOHANG) > 0)  ;         /* clean up zombies */
   }
}
