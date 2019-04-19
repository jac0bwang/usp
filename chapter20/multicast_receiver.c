#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "restart.h"
#include "uiciudp.h"
#define BUFSIZE 1024

int main(int argc, char *argv[]) {
   char buf[BUFSIZE];
   ssize_t bytesread;
   char hostinfo[BUFSIZE];
   int mcastfd;
   u_buf_t mcastinfo;
   u_port_t mcastport;
   u_buf_t senderinfo;

   if (argc != 3) {
      fprintf(stderr, "Usage: %s multicast-address multicast-port\n", argv[0]);
      return 1;
   }

   mcastport = (u_port_t)atoi(argv[2]);          /* join the multicast group */
   if ((mcastfd = u_join(argv[1], mcastport, &mcastinfo)) == -1) {
      perror("Failed to join multicast group");
      return 1;
   }

   u_gethostinfo(&mcastinfo, buf, BUFSIZE);
   fprintf(stderr, "Info: %s\n", buf);
   fprintf(stderr, "mcastfd is %d\n", mcastfd);

                 /* read information from multicast, send to standard output */
   while ((bytesread = u_recvfrom(mcastfd, buf, BUFSIZE, &senderinfo)) > 0) {
      u_gethostinfo(&senderinfo, hostinfo, BUFSIZE);
      if ((r_write(STDOUT_FILENO, hostinfo, strlen(hostinfo)) == -1) ||
          (r_write(STDOUT_FILENO, buf, bytesread) == -1)) {
         perror("Failed to echo message received to standard output");
         break;
      }  
   }
   return 0;
}
