#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "restart.h" 
#include "uiciudp.h" 
#define BUFSIZE 1024

int request_reply_timeout(int requestfd, void* request, int reqlen,
                  char* server, int serverport, void *reply, int replen,
                  double timeout);

int main(int argc, char *argv[]) {
   ssize_t bytesread, byteswritten;
   char reply[BUFSIZE];  
   char request[BUFSIZE]; 
   int requestfd;
   u_port_t serverport;
   double timeout;
  
   if (argc != 4) {
      fprintf(stderr, "Usage: %s servername serverport timeout\n", argv[0]);
      return 1;  
   }
   serverport = (u_port_t) atoi(argv[2]);
   timeout = atof(argv[3]);
   if ((requestfd = u_openudp(0)) == -1) {     /* create unbound UDP endpoint */
      perror("Failed to create UDP endpoint");
      return 1;
   }
   sprintf(request, "[%ld]\n", (long)getpid());    /* create a request string */
                 /* use request-reply protocol with timeout to send a message */
   bytesread = request_reply_timeout(requestfd, request, strlen(request) + 1,
                        argv[1], serverport, reply, BUFSIZE, timeout);
   if (bytesread == -1)
      perror("Failed to complete request_reply_timeout");
   else {
      byteswritten = r_write(STDOUT_FILENO, reply, bytesread);
      if (byteswritten == -1)
         perror("Failed to echo server reply");
   }
   if ((r_close(requestfd) == -1) || (bytesread == -1) || (byteswritten == -1)) 
      return 1;
   return 0;
}
