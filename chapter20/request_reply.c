#include <sys/types.h>
#include "uiciudp.h"

int request_reply(int requestfd, void* request, int reqlen,
                  char* server, int serverport, void *reply, int replen) {
   ssize_t nbytes;
   u_buf_t senderinfo;
                                                         /* send the request */
   nbytes = u_sendtohost(requestfd, request, reqlen, server, serverport);
   if (nbytes == -1)
      return (int)nbytes;
                        /* wait for a response, restart if from wrong server */
   while ((nbytes = u_recvfrom(requestfd, reply, replen, &senderinfo)) >= 0 )  
      if (u_comparehost(&senderinfo, server, serverport))    /* sender match */
         break;
   return (int)nbytes;
}
