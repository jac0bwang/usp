/* uiciudp.c udp sockets implementation */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include "restart.h"
#include "uiciname.h"
#include "uiciudp.h"

/*
 *                           u_openudp
 * Return a file descriptor.
 *  It is bound to the given port if the port is positive.
 *
 * parameter:
 *        port = number of port to bind to
 * returns:  file descriptor if successful
 *           -1 on error and sets errno
 */
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

/*
 *                           u_recvfrom
 *
 * Retrieve information from a file descriptor.
 *
 * parameters:
 *       fd = socket file descriptor
 *       buf = buffer that receives the data
 *       nbytes = number of bytes to retrieve
 *       ubufp = a pointer to a buffer of type u_buf_t
 * returns:
 *      the number of bytes read if successful.
 *         ubufp is filled with information about the sending host and port
 *      -1 on error and sets errno
 */

ssize_t u_recvfrom(int fd, void *buf, size_t nbytes, u_buf_t *ubufp) {
   int len;
   struct sockaddr *remote;
   int retval;

   len = sizeof (struct sockaddr_in);
   remote = (struct sockaddr *)ubufp;
   while (((retval = recvfrom(fd, buf, nbytes, 0, remote, &len)) == -1) &&
           (errno == EINTR)) ;  
   return retval;
}

/*
 *                           u_recvfromtimed
 *
 * Retrieve information from a file descriptor with a timeout.
 *
 * parameters:
 *       fd = socket file descriptor
 *       buf = buffer to receive the data
 *       nbytes = number of bytes to retrieve
 *       ubufp = a pointer to a buffer of type u_buf_t
 *       seconds = timeout in seconds
 * returns:
 *      number of bytes received if successful
 *      -1 on error and sets errno
 */

ssize_t u_recvfromtimed(int fd, void *buf, size_t nbytes, u_buf_t *ubufp,
                         double seconds) {
   int len;
   struct sockaddr *remote;
   int retval;
   struct timeval timedone;

   timedone = add2currenttime(seconds);
   if (waitfdtimed(fd, timedone) == -1)
      return (ssize_t)(-1);
   len = sizeof (struct sockaddr_in);
   remote = (struct sockaddr *)ubufp;
   while (((retval = recvfrom(fd, buf, nbytes, 0, remote, &len)) == -1) &&
           (errno == EINTR)) ;  
   return retval;
}

/*
 *                           u_gethostname
 *
 * Get the host name from a buffer of type u_buf_t
 *
 * parameters:
 *       ubufp = a pointer to a buffer of type u_buf_t that was
 *          filled by u_recvfrom
 *       hostn = a buffer of size hostnsize
 *       hostsize = the size of the hostn buffer
 * returns:
 *      hostn is filled with the name of the host, possibly truncated.
 */

void u_gethostname(u_buf_t *ubufp, char *hostn, int hostnsize) {
   struct sockaddr_in *remotep;

   remotep = (struct sockaddr_in *)ubufp;
   addr2name(remotep->sin_addr, hostn, hostnsize);
}

/*
 *                           u_gethostinfo
 *
 * Get a printable string containing the host name and port
 *
 * parameters:
 *       ubufp = a pointer to a buffer of type u_buf_t that was
 *          filled by u_recvfrom
 *       info = a buffer to hold the returned string
 *       infosize = the size of the info buffer
 * returns:
 *      a string is put in info, possibly truncated
 */
void u_gethostinfo(u_buf_t *ubufp, char *info, int infosize) {
   int len;
   int portnumber;

   portnumber = ntohs(ubufp->sin_port);
   len = snprintf(info, infosize, "port number is %d on host ", portnumber);
   info[infosize-1] = 0;                              /* in case name not fit */
   if (len >= infosize) return;
   u_gethostname(ubufp, info+len, infosize-len);
}

 
/*
 *                           u_comparehost
 *
 * Compare the given host and port with the info in a u_buf_t structure
 *
 * parameters:
 *       ubufp = a pointer to a buffer of type u_buf_t that was
 *          filled by u_recvfrom
 *       hostn = a string representing the host name
 *       port  = a port number
 * returns:
 *      1 if match
 *      0 if no match
 */
 
int u_comparehost(u_buf_t *ubufp, char *hostn, u_port_t port) {
   in_addr_t addr;
   struct sockaddr_in *remotep;

   remotep = (struct sockaddr_in *)ubufp;
   if ((port != ntohs(remotep->sin_port)) ||
       (name2addr(hostn, &addr) == -1) ||
       (memcmp(&(remotep->sin_addr.s_addr), &addr, sizeof(in_addr_t)) != 0))
      return 0;
   return 1;
}

 
/*
 *                           u_sendto
 *
 * Send information atomically to a remote host, using the buffer filled in
 * by recvfrom
 *
 * This is almost the same as sendto except that
 *   it retries if interrupted by a signal and
 *   the length of the buffer indicating the destination is not passed
 *
 * parameters:
 *       fd = file descriptor
 *       buf = buffer to be output
 *       nbytes = number of bytes to send
 *       ubufp = a pointer to a buffer of type u_buf_t that was
 *          filled by u_recvfrom
 * returns:
 *      the number of bytes that were sent (may not have been received)
 *      -1 on error and sets errno
 */

ssize_t u_sendto(int fd, void *buf, size_t nbytes, u_buf_t *ubufp) {
   int len;
   struct sockaddr *remotep;
   int retval;

   len = sizeof(struct sockaddr_in);
   remotep = (struct sockaddr *)ubufp;
   while (((retval = sendto(fd, buf, nbytes, 0, remotep, len)) == -1) &&
           (errno == EINTR)) ;  
   return retval;
}
 
/*
 *                           u_sendtohost
 *
 * Send information atomically to a remote host given the host name and port
 * 
 * parameters:
 *       fd = file descriptor
 *       buf = buffer to be output
 *       nbyte = number of bytes to send
 *       port = the port number to send to
 *       hostn = a string containing the name of the destination host
 * returns:
 *      the number of bytes that were sent (may not have been received)
 *      -1 on error and sets errno
 */
   
ssize_t u_sendtohost(int fd, void *buf, size_t nbytes, char *hostn,
                     u_port_t port) {
   struct sockaddr_in remote;

   if (name2addr(hostn, &(remote.sin_addr.s_addr)) == -1) {
      errno = EINVAL;
      return -1;
   }
   remote.sin_port = htons((short)port);
   remote.sin_family = AF_INET;
   return u_sendto(fd, buf, nbytes, &remote);
}

/*
 *                           u_join
 *
 * Join a multicast group
 *
 * parameters:
 *       IP_address = string representing the IP address of the group
 *       port = port number of multicast group
 *       ubufp = buffer to be filled in u_join
 * returns:
 *      a file descriptor on success
 *      -1 on error and sets errno
*/
int u_join(char *IP_address, u_port_t port, u_buf_t *ubufp) {
   int mcastfd;
   struct ip_mreq tempaddress;

   if ((mcastfd = u_openudp(port)) == -1)
      return mcastfd;
   
   tempaddress.imr_multiaddr.s_addr = inet_addr(IP_address);
   tempaddress.imr_interface.s_addr = htonl(INADDR_ANY);

        /* Join the multicast group. Let kernel choose the interface */
   if (setsockopt(mcastfd, IPPROTO_IP, IP_ADD_MEMBERSHIP,
                   &tempaddress, sizeof(tempaddress)) == -1)
      return -1;
   ubufp->sin_family = AF_INET;
   ubufp->sin_addr.s_addr = inet_addr(IP_address);
   ubufp->sin_port = htons((short)port);
   return mcastfd;
}

/* This version leaves the group but keeps the file descriptor open and
   still bound to the same port.  It can still receive messages on the port,
   but only those addressed directly to the given host.
*/
/*
 *                           u_leave
 *
 * Leave a multicast group.  Messages can still be received on the port
 * if they are directly addressed to the host.
 *
 * parameters:
 *       mcastfd = previously opened file descriptor returned by u_join
 *       ubufp = buffer filled in by previous u_join
 * returns:
 *      0 on success
 *      -1 on error with errno set
*/
int u_leave(int mcastfd, u_buf_t *ubufp) {  
   struct ip_mreq tempaddress;
 
   memcpy(&(tempaddress.imr_multiaddr),
         &(ubufp->sin_addr), sizeof(struct in_addr));   
   tempaddress.imr_interface.s_addr = htonl(INADDR_ANY);
   return setsockopt(mcastfd, IPPROTO_IP, IP_DROP_MEMBERSHIP,
                   &tempaddress, sizeof(tempaddress));
}
