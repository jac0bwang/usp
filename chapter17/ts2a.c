#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ntpvm.h"
#define MAX_LINE_SIZE 100

static char *typename[] = {"Start Task", "Data", "Broadcast", "Done",
                         "Terminate", "Barrier"};
 
int main(void) {
   char buf[MAX_PACK_SIZE + MAX_LINE_SIZE];
   int bytesread;
   taskpacket_t pack;
   int wsize;
     
   wsize = sizeof(taskpacket_t);
   fprintf(stderr, "***** Waiting for first packet\n");
   for( ; ; ) {
      bytesread =  read(STDIN_FILENO, &pack, wsize);
      if (bytesread == 0) {
         fprintf(stderr, "End-of-file received\n");
         break; 
      }
      if (bytesread != wsize) {
         fprintf(stderr, "Error reading packet header\n");
         return 1;
      }
      if ( (pack.type < 0) || (pack.type >= NUMTYPES) ) {
         fprintf(stderr, "Got invalid packet\n");
         return 1;
      }
      printf("Received packet header of type %s\n",typename[pack.type]);
      printf("   compid = %d, taskid = %d, length = %d\n",
             pack.compid, pack.taskid, pack.length);
      fflush(stdout);
      if (pack.length > MAX_PACK_SIZE) {
         fprintf(stderr, "Task data is too long\n");
         return 1; 
      }
      if (read(STDIN_FILENO, buf, pack.length) != pack.length) {
         fprintf(stderr, "Error reading packet data\n");
         return 1;
      }
      write(STDOUT_FILENO, buf, pack.length);
      fprintf(stderr, "***** Waiting for next packet\n");
   }
   return 0;
}    
