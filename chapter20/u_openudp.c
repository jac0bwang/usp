#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include "restart.h"
#include "uiciudp.h"

int u_openudp(u_port_t port) {
   int error;
   int one = 1;
   struct sockaddr_in server;
   int sock;

   if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
      return -1;
   if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)) == -1) {
      error = errno;
      r_close(sock);
      errno = error;
      return -1;
   }
   if (port > 0) {
      server.sin_family = AF_INET;
      server.sin_addr.s_addr = htonl(INADDR_ANY);
      server.sin_port = htons((short)port);
      if (bind(sock, (struct sockaddr *)&server, sizeof(server)) == -1) {
         error = errno;
         r_close(sock);
         errno = error;
         return -1;
      }  
   }   
   return sock;
}
