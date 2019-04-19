#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "uici.h"
#include "restart.h"

int copy2files(int fromfd1, int tofd1, int fromfd2, int tofd2);
 
int main(int argc, char *argv[]) {
   int bytescopied;
   int communfd;
   u_port_t portnumber;
 
   if (argc != 3) {
      fprintf(stderr, "Usage: %s host port\n", argv[0]);
      return 1;
   }
   portnumber = (u_port_t)atoi(argv[2]);
   if ((communfd = u_connect(portnumber, argv[1])) == -1) {
      perror("Failed to establish connection");
      return 1;  
   }
   fprintf(stderr, "[%ld]:connection made to %s\n", (long)getpid(), argv[1]);
   bytescopied = copy2files(communfd, STDOUT_FILENO, STDIN_FILENO, communfd);
   fprintf(stderr, "[%ld]:transferred %d bytes\n", (long)getpid(), bytescopied);
   return 0;
}
