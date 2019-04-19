/* uici.c  sockets implementation */

/*#include <stdio.h>*/
#include <unistd.h>
/*#include <string.h>*/
/*#include <netdb.h>*/
#include <signal.h>
/*#include <ctype.h>*/
/*#include <sys/types.h>*/
#include <sys/socket.h>
/*#include <netinet/in.h>*/
/*#include <netinet/tcp.h>*/
/*#include <arpa/inet.h>*/
#include <errno.h>
#include "uiciname.h"
#include "uici.h"

#define MAXBACKLOG 50

/* return 1 if error, 0 if OK */
static int u_ignore_sigpipe()
{
   struct sigaction act;

   if (sigaction(SIGPIPE, (struct sigaction *)NULL, &act) < 0)
      return 1;
   if (act.sa_handler == SIG_DFL) {
      act.sa_handler = SIG_IGN;
      if (sigaction(SIGPIPE, &act, (struct sigaction *)NULL) < 0)
         return 1;
   }   
   return 0;
}

/*
 *                           u_open
 * Return a file descriptor which is bound to the given port.
 *
 * parameter:
 *        s = number of port to bind to
 * returns:  file descriptor if successful
 *           -1 on error and sets errno
 */
int u_open(u_port_t port)
{
   struct sockaddr_in server;
   int sock;
   int true = 1;
   int error;  

   if ( (u_ignore_sigpipe() != 0) ||
        ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) )
      return -1; 

   if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&true,
                  sizeof(true)) < 0) {
      error = errno;
      close(sock); 
      errno = error;
      return -1;
   }
 
   server.sin_family = AF_INET;
   server.sin_addr.s_addr = htonl(INADDR_ANY);
   server.sin_port = htons((short)port);
   if ( (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0) ||
        (listen(sock, MAXBACKLOG) < 0) ) {
      error = errno;
      close(sock);
      errno = error;
      return -1;
   }
   return sock;
}

/*
 *                           u_accept
 * Wait for a from a host on a specified port.
 *
 * parameters:
 *      fd = file descriptor previously bound to listening port
 *      hostn = name of host to listen for
 *      hostnsize = size of hostn buffer
 * returns:  communication file descriptor or -1 on error
 *
 * comments: This function is used by the server to wait for a
 * communication.  It blocks until a remote request is received
 * from the port bound to the given file descriptor.
 * hostn is filled with an ASCII string containing the remote
 * host name.  It must point to a buffer of size at least hostnsize.
 * If the name does not fit, as much of the name as is possible is put
 * into the buffer.
 * If hostn is NULL or hostnsize <= 0, no hostname is copied.
 */
int u_accept(int fd, char *hostn, int hostnsize)
{
   int len = sizeof(struct sockaddr);
   struct sockaddr_in net_client;
   int retval;

   while ( ((retval =
           accept(fd, (struct sockaddr *)(&net_client), &len)) == -1) &&
          (errno == EINTR) )
      ;  
   if ( (retval == -1) || (hostn == NULL) || (hostnsize <= 0) )
      return retval;
   addr_to_name(net_client.sin_addr,hostn,hostnsize);
   return retval;
}

/*
 *                           u_connect
 * Initiate communication with a remote server.
 *
 * parameters:
 *     port  = well-known port on remote server
 *     hostn = character string giving the Internet name of the
 *             remote machine
 * returns:  the file descriptor used for communication if successful
 *           -1 on error on system error that sets errno
 *           U_EHOST if hostn cannot be resolved
 *           U_ECONNECTION if connection fails
 */
int u_connect(u_port_t port, char *hostn)
{
   int retval;
   struct sockaddr_in server;
   int sock;
   int error;

   if (name_to_addr(hostn,&(server.sin_addr.s_addr)) < 0) {
      errno = EINVAL;
      return -1;
   }
   server.sin_port = htons((short)port);
   server.sin_family = AF_INET;

   if ( (u_ignore_sigpipe() != 0) ||
        ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) )
      return -1;

   while ( ((retval =
       connect(sock, (struct sockaddr *)&server, sizeof(server))) == -1)
        && (errno == EINTR) )
      ;  
   if (retval == -1) {
        error = errno;
        close(sock);
        errno = error;
        return -1;
   }
   return sock;
}
