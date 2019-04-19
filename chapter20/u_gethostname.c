#include "uiciname.h"
#include "uiciudp.h"

void u_gethostname(u_buf_t *ubufp, char *hostn, int hostnsize) {
   struct sockaddr_in *remotep;

   remotep = (struct sockaddr_in *)ubufp;
   addr2name(remotep->sin_addr, hostn, hostnsize);
}
