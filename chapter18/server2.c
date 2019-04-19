#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "uici.h"
int copy2files(int fromfd1, int tofd1, int fromfd2, int tofd2);

/*                                  
 *                       UICI Server
 *  Open a UICI port specified as a command-line argument
 *  and wait for a client request.  When a request arrives
 *  use the provided communication file descriptor to read
 *  from the UICI connection and echo to standard output
 *  until the connection is terminated.  Then resume
 *  waiting for another request.
 */
int main(int argc, char *argv[])
{
   u_port_t portnumber;
   int listenfd;
   int communfd;
   char client[MAX_CANON];
   int bytes_copied;
 
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
   for ( ; ;) {
      if ((communfd = u_accept(listenfd, client, MAX_CANON)) != -1) {
         fprintf(stderr, "A connection has been received from %s\n",client);
         bytes_copied =
            copy2files(communfd, STDOUT_FILENO, STDIN_FILENO, communfd);
         fprintf(stderr, "[%ld]:Bytes transferred = %d\n",
                          (long) getpid(), bytes_copied);
         close(communfd);
      }
      else
         perror("Accept failed");
   }
}
