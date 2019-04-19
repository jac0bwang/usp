#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "restart.h"
#include "uici.h"
#define BUFSIZE 1000
 
int main(int argc, char *argv[]) {
   char bufrecv[BUFSIZE];
   char bufsend[BUFSIZE];
   int bytesrecvd;
   int communfd;     
   int i;
   u_port_t portnumber;
   int totalrecvd;
 
   if (argc != 3) {
      fprintf(stderr, "Usage: %s host port\n", argv[0]);
      return 1;
   }
   for (i = 0; i < BUFSIZE; i++)                    /* set up a test message */
      bufsend[i] = (char)(i%26 + 'A');
   portnumber = (u_port_t)atoi(argv[2]);
   if ((communfd = u_connect(portnumber, argv[1])) == -1) {
      perror("Failed to establish connection");
      return 1;
   }
   if (r_write(communfd, bufsend, BUFSIZE) != BUFSIZE) {
      perror("Failed to write test message");
      return 1;
   }
   totalrecvd = 0;
   while (totalrecvd < BUFSIZE) {
      bytesrecvd = r_read(communfd, bufrecv + totalrecvd, BUFSIZE - totalrecvd);
      if (bytesrecvd <= 0) {
         perror("Failed to read response message");
         return 1;
      }
      totalrecvd += bytesrecvd;
   }
   for (i = 0; i < BUFSIZE; i++)
      if (bufsend[i] != bufrecv[i])
         fprintf(stderr, "Byte %d read does not agree with byte written\n", i);
   return 0;
}
