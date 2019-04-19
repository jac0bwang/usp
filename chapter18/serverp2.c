#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "restart.h"
#include "uici.h"
 
int copy2files(int fromfd1, int tofd1, int fromfd2, int tofd2);
 
/*
 *                       UICI Server
 *  Open a UICI port specified as a command-line argument
 *  and wait for requests.  When a request arrives,
 *  fork a child to handle the communication and resume
 *  waiting for another request.
 */
int main(int argc, char *argv[])
{
   u_port_t portnumber;
   int listenfd;
   int communfd;
   char client[MAX_CANON];
   int bytes_copied;
   pid_t child;
 
   if (argc != 2) {
      fprintf(stderr, "Usage: %s port\n", argv[0]);
      return 1;   
   }  
 
   portnumber = (u_port_t) atoi(argv[1]);
   if ((listenfd = u_open(portnumber)) < 0) {
      perror("Listen endpoint creation failed");
      return 1;
   }
 
   fprintf(stderr, "[%ld]: Waiting for the first connection on port %d\n",
                    (long)getpid(), (int)portnumber);
   for ( ; ; ) {
      if ((communfd = u_accept(listenfd, client, MAX_CANON)) != -1) {
         fprintf(stderr, "[%ld]: A connection has been received from %s\n",
                 (long) getpid(), client);
         if ((child = fork()) == -1)
            perror("Could not fork a child");
 
         if (child == 0) {                            /* child code */
            r_close(listenfd);
            bytes_copied =
               copy2files(communfd, STDOUT_FILENO, STDIN_FILENO, communfd);
            r_close(communfd);
            fprintf(stderr, "[%ld]:Bytes transferred = %d\n",
                           (long) getpid(), bytes_copied);
            return 0;
         } else {                                    /* parent code */
            r_close(communfd);
            while (r_waitpid(-1, NULL, WNOHANG) > 0) ;  /* clean up zombies */
         }
      }
      else
         perror("Accept failed");
   }
}
