#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "uici.h"

#define MAXBACKLOG 50

int u_ignore_sigpipe(void); 

int u_open(u_port_t port) {
   int error;  
   struct sockaddr_in server;
   int sock;
   int true = 1;
 
   if ((u_ignore_sigpipe() == -1) ||
        ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1))
      return -1; 
 
   if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&true,
                  sizeof(true)) == -1) {
      error = errno;
      while ((close(sock) == -1) && (errno == EINTR));
      errno = error;
      return -1;   
   }
 
   server.sin_family = AF_INET;
   server.sin_addr.s_addr = htonl(INADDR_ANY);
   server.sin_port = htons((short)port);
   if ((bind(sock, (struct sockaddr *)&server, sizeof(server)) == -1) ||
        (listen(sock, MAXBACKLOG) == -1)) {
      error = errno;
      while ((close(sock) == -1) && (errno == EINTR));
      errno = error;
      return -1;   
   }
   return sock;
}
