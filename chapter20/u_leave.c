#include <string.h>
#include <sys/socket.h>
#include "uiciudp.h"

int u_leave(int mcastfd, u_buf_t *ubufp) {
   struct ip_mreq tempaddress;

   memcpy(&(tempaddress.imr_multiaddr),
         &(ubufp->sin_addr), sizeof(struct in_addr));
   tempaddress.imr_interface.s_addr = htonl(INADDR_ANY);
   return setsockopt(mcastfd, IPPROTO_IP, IP_DROP_MEMBERSHIP,
                   &tempaddress, sizeof(tempaddress));
}
