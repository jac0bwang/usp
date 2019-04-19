#include <sys/types.h>
#include "uiciudp.h"

int request_reply_timeout(int requestfd, void* request, int reqlen,
                  char* server, int serverport, void *reply, int replen,
                  double timeout) {
   ssize_t nbytes;
   u_buf_t senderinfo;

                                                        /* send the request */
   nbytes = u_sendtohost(requestfd, request, reqlen, server, serverport);
   if (nbytes == -1)
      return -1;
       /* wait timeout seconds for a response, restart if from wrong server */
   while ((nbytes = u_recvfromtimed(requestfd, reply, replen,
                                         &senderinfo, timeout)) >= 0 &&
                (u_comparehost(&senderinfo, server, serverport) == 0)) ;
   return (int)nbytes;
}
