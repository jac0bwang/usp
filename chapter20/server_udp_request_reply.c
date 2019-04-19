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
   port = (u_port_t) atoi(argv[1]);         /* create UDP endpoint for port */
   if ((requestfd = u_openudp(port)) == -1) {  
      perror("Failed to create UDP endpoint");
      return 1;
   }
   for ( ; ; ) {                /* process client requests and send replies */
      bytesread = u_recvfrom(requestfd, buf, BUFSIZE, &senderinfo);
      if (bytesread == -1) {
         perror("Failed to receive client request");
         continue;
      }
      u_gethostinfo(&senderinfo, hostinfo, BUFSIZE);
      if ((r_write(STDOUT_FILENO, hostinfo, strlen(hostinfo)) == -1) ||
          (r_write(STDOUT_FILENO, buf, bytesread) == -1)) {
         perror("Failed to echo client request to standard output");
      }
      if (u_sendto(requestfd, buf, bytesread, &senderinfo) == -1) {
         perror("Failed to send the reply to the client");
      }
   }  
}
