#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "restart.h"
#include "uiciudp.h"
#define BUFSIZE 1024 
 
int main(int argc, char *argv[]) {
   ssize_t byteswritten;
   char request[BUFSIZE];
   int requestfd;  
   int rlen;
   u_port_t serverport;
 
   if (argc != 3) {
      fprintf(stderr, "Usage: %s servername serverport\n", argv[0]);
      return 1;
   }
   serverport = (u_port_t) atoi(argv[2]);
   if ((requestfd = u_openudp(0)) == -1) {     /* create unbound UDP endpoint */
      perror("Failed to create UDP endpoint");
      return 1;
   }
   sprintf(request, "[%ld]\n", (long)getpid());           /* create a request */
   rlen = strlen(request);
    /* use  simple-request protocol to send a request to (server, serverport) */
   byteswritten = u_sendtohost(requestfd, request, rlen, argv[1], serverport);
   if (byteswritten == -1)
      perror("Failed to send");
   if (r_close(requestfd) == -1 || byteswritten == -1)
      return 1;
   return 0;
}
