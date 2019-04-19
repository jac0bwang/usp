#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "restart.h"
#include "uiciudp.h"

#define BUFSIZE 1024
int main(int argc, char *argv[]) {
   char buf[BUFSIZE];
   int fd;
   u_port_t port;
   ssize_t nbytes;

   if (argc != 3) {
      fprintf(stderr, "Usage: %s host port\n", argv[0]);
      return 1;
   }

   if ((fd = u_openudp(0)) < 0) {
      perror("UDP endpoint creation failed");
      return 1;
   }

   port = (u_port_t)atoi(argv[2]);
   /* send info read from standard input */
   while ((nbytes = r_read(STDIN_FILENO, buf, BUFSIZE)) > 0) {
      if ( (nbytes = u_sendtohost(fd, buf, nbytes, argv[1], port)) < 0) {
         perror("send failed");
         return 1;
      }  
   }
   return 0;
}
