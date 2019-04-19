#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "restart.h"
#include "uici.h"
 
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
      perror("Failed to make connection");
      return 1;
   }
   fprintf(stderr, "[%ld]:connected %s\n", (long)getpid(), argv[1]);
   bytescopied = copyfile(STDIN_FILENO, communfd);
   fprintf(stderr, "[%ld]:sent %d bytes\n", (long)getpid(), bytescopied);
   return 0;
}
