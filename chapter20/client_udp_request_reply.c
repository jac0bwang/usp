#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "restart.h"
#include "uiciudp.h"
#define BUFSIZE 1024

int request_reply(int requestfd, void* request, int reqlen,
                  char* server, int serverport, void *reply, int replen);

int main(int argc, char *argv[]) {
   ssize_t bytesread, byteswritten;
   char reply[BUFSIZE];
   char request[BUFSIZE];
   int requestfd;
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
                              /* use request-reply protocol to send a message */
   bytesread = request_reply(requestfd,  request, strlen(request)+1,
                         argv[1], serverport, reply, BUFSIZE);
   if (bytesread == -1) 
      perror("Failed to do request_reply");
   else {
      byteswritten = r_write(STDOUT_FILENO, reply, bytesread);
      if (byteswritten == -1)
         perror("Failed to echo server reply");
   }
   if ((r_close(requestfd) == -1) || (bytesread  == -1) || (byteswritten == -1))
      return 1;
   return 0;
}
