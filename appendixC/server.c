#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "restart.h"
#include "uici.h"

int main(int argc, char *argv[]) {
   int bytescopied;
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
   fprintf(stderr, "[%ld]:waiting for the first connection on port %d\n",
                    (long)getpid(), (int)portnumber);
   for ( ; ; ) {
      if ((communfd = u_accept(listenfd, client, MAX_CANON)) == -1) {
         perror("Failed to accept connection");
         continue;
      }
      fprintf(stderr, "[%ld]:connected to %s\n", (long)getpid(), client);
      bytescopied = copyfile(communfd, STDOUT_FILENO);
      fprintf(stderr, "[%ld]:received %d bytes\n", (long)getpid(), bytescopied);
      if (r_close(communfd) == -1)
         perror("Failed to close communfd\n");
   }
}
