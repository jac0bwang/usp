#include <string.h>
#include <sys/socket.h>
#include "uiciname.h"
#include "uiciudp.h"

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
