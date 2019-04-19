#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "restart.h"
#include "uiciudp.h"

#define BUFSIZE 1024
int main(int argc, char *argv[]) {
   char buf[BUFSIZE];
   char host_info[BUFSIZE];
   int mcastfd;
   u_buf_t mcast_info;
   u_port_t mcastport;
   ssize_t nbytes_read;
   u_buf_t sender_info;
   int count;

   if (argc != 3) {
      fprintf(stderr, "Usage: %s Multicast-Address Multicast-Port\n", argv[0]);
      return 1;
   }

                                                  /* join the multicast group */
   mcastport = (u_port_t)atoi(argv[2]);
   if ((mcastfd = u_join(argv[1], mcastport, &mcast_info)) == -1) {
      perror("Receiver failed to join multicast group");
      return 1;
   }
   u_gethostinfo(&mcast_info,buf,BUFSIZE);
   fprintf(stderr,"Info: %s\n",buf);
   fprintf(stderr,"mcastfd is %d\n",mcastfd);

 
                            /* multicast information read from standard input */
   count = 0;
   while ((nbytes_read = u_recvfrom(mcastfd, buf, BUFSIZE, &sender_info)) > 0) {
      u_gethostinfo(&sender_info, host_info, BUFSIZE);
      if ((r_write(STDOUT_FILENO, host_info, strlen(host_info)) == -1) ||
          (r_write(STDOUT_FILENO, buf, nbytes_read) == -1)) {
         perror("Error echoing sender or message to standard output");
         break;
      }  
      count++;
      if (count == 5) {
         fprintf(stderr,"Leaving group\n");
         if (u_leave(mcastfd,&mcast_info) == -1)
            perror("Error leaving group");
      }  

   }
   return 0;
}
