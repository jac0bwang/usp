#include <arpa/inet.h>
#include <sys/socket.h>
#include "uiciudp.h"

int u_join(char *IP_address, u_port_t port, u_buf_t *ubufp) {
   int mcastfd;
   struct ip_mreq tempaddress;

   if ((mcastfd = u_openudp(port)) == -1)
      return mcastfd;

   tempaddress.imr_multiaddr.s_addr = inet_addr(IP_address);
   tempaddress.imr_interface.s_addr = htonl(INADDR_ANY);

        /* join the multicast group; let kernel choose the interface */
   if (setsockopt(mcastfd, IPPROTO_IP, IP_ADD_MEMBERSHIP,
                   &tempaddress, sizeof(tempaddress)) == -1)
      return -1;

   ubufp->sin_family = AF_INET;
   ubufp->sin_addr.s_addr = inet_addr(IP_address);
   ubufp->sin_port = htons((short)port);
   return mcastfd;
}
