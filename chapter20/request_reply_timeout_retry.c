#include <stdio.h>
#include <errno.h>
#include "uiciudp.h"    

int request_reply_timeout_retry(int requestfd, void* request, int reqlen,
                  char* server, int serverport, void *reply, int replen,
                  double timeout, int maxretries) {
   ssize_t nbytes;
   int retries;  
   u_buf_t senderinfo;   

   retries = 0;  
   while (retries < maxretries) {
                                   /* send process ID to (server, serverport) */
       nbytes = u_sendtohost(requestfd, request, reqlen, server, serverport);
       if (nbytes == -1)
          return -1;                                         /* error on send */
         /* wait timeout seconds for a response, restart if from wrong server */
       while (((nbytes = u_recvfromtimed(requestfd, reply, replen,
                                            &senderinfo, timeout)) >= 0) &&
              (u_comparehost(&senderinfo, server, serverport) == 0)) ;
       if (nbytes >= 0) 
          break; 
       retries++;
   }
   if (retries >= maxretries) {
      errno = ETIME;
      return -1;
   }
   return (int)nbytes;          
}
