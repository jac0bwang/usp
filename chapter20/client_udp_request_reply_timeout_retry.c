#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "restart.h" 
#include "uiciudp.h" 
#define BUFSIZE 1024

int request_reply_timeout_retry(int requestfd, void* request, int reqlen,
                  char* server, int serverport, void *reply, int replen,
                  double timeout, int maxretries);

int main(int argc, char *argv[]) {
   ssize_t bytesread, byteswritten;
   char request[BUFSIZE]; 
   int requestfd;
   char reply[BUFSIZE];  
   u_port_t serverport;
   double timeout;
   int retries;
  
   if (argc != 5) {
      fprintf(stderr, "Usage: %s servername serverport timeout retries\n",
              argv[0]);
      return 1;  
   }
   serverport = (u_port_t) atoi(argv[2]);
   timeout = atof(argv[3]);
   retries = atof(argv[4]);
   if ((requestfd = u_openudp(0)) == -1) {  /* create an unbound UDP endpoint */
      perror("UDP endpoint creation failed");
      return 1;
   }
   sprintf(request, "[%ld]\n", (long)getpid());      /* create request string */
                 /* use request-reply protocol with timeout to send a message */
   bytesread = request_reply_timeout_retry(requestfd, request,
                        strlen(request) + 1, argv[1],
                        serverport, reply, BUFSIZE, timeout, retries);
   if (bytesread < 0)
      perror("Failed to complete request_reply_timeout_retry");
   else {
      byteswritten = r_write(STDOUT_FILENO, reply, bytesread);
      if (byteswritten < 0)
         perror("Failed to echo server reply");
   }
   if (r_close(requestfd) == -1 || bytesread < 0 || byteswritten < 0)
      return 1;
   return 0;
}
