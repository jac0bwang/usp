#include <ctype.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "uiciname.h"
#include "uici.h"

int u_ignore_sigpipe(void);

int u_connect(u_port_t port, char *hostn) {
   int error;
   int retval;
   struct sockaddr_in server;
   int sock;
   fd_set sockset;

   if (name2addr(hostn,&(server.sin_addr.s_addr)) == -1) {
      errno = EINVAL;
      return -1;
   }
   server.sin_port = htons((short)port);
   server.sin_family = AF_INET;

   if ((u_ignore_sigpipe() == -1) ||
        ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1))
      return -1;

   if (((retval =
       connect(sock, (struct sockaddr *)&server, sizeof(server))) == -1) &&
       ((errno == EINTR) || (errno == EALREADY))) {          /* asynchronous */
       FD_ZERO(&sockset);
       FD_SET(sock, &sockset);
       while (((retval = select(sock+1, NULL, &sockset, NULL, NULL)) == -1)
           && (errno == EINTR)) {
          FD_ZERO(&sockset);
          FD_SET(sock, &sockset);
       }
   }
   if (retval == -1) {
        error = errno;
        while ((close(sock) == -1) && (errno == EINTR));
        errno = error;
        return -1;
   }
   return sock;
}
