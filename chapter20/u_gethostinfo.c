#include <stdio.h>
#include "uiciudp.h"
#define BUFSIZE 1024

void u_gethostinfo(u_buf_t *ubufp, char *info, int infosize) {
   int len;
   int portnumber;

   portnumber = ntohs(ubufp->sin_port);
   len = snprintf(info, infosize, "port number is %d on host ", portnumber);
   info[infosize-1] = 0;                         /* in case name did not fit */
   if (len >= infosize) return;
   u_gethostname(ubufp, info+len, infosize-len);
}
