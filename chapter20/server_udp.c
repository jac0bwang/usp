#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "restart.h"
#include "uiciudp.h"
#define BUFSIZE 1024

int main(int argc, char *argv[]) {
   char buf[BUFSIZE];
   ssize_t bytesread;
   char hostinfo[BUFSIZE];
   u_port_t port;
   int requestfd;
   u_buf_t senderinfo;

   if (argc != 2) {
      fprintf(stderr, "Usage: %s port\n", argv[0]);
      return 1;
   }
   port = (u_port_t) atoi(argv[1]);        /* create communication endpoint */
   if ((requestfd = u_openudp(port)) == -1) {
      perror("Failed to create UDP endpoint");
      return 1;
   }
   for ( ; ; ) {                                 /* process client requests */
      bytesread = u_recvfrom(requestfd, buf, BUFSIZE, &senderinfo);
      if (bytesread < 0) {
         perror("Failed to receive request");
         continue;
      }
      u_gethostinfo(&senderinfo, hostinfo, BUFSIZE);
      if ((r_write(STDOUT_FILENO, hostinfo, strlen(hostinfo)) == -1) ||
          (r_write(STDOUT_FILENO, buf, bytesread) == -1)) {
         perror("Failed to echo reply to standard output");
      }
   }     
}
