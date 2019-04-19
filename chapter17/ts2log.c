#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ntpvm.h"
#include "restart.h"
#include "rlogging.h"
#define MAX_LINE_SIZE 100

static char *typename[] = {"Start Task", "Data", "Broadcast", "Done",
                         "Terminate", "Barrier"};

int main(void) {
   char buf[MAX_PACK_SIZE + MAX_LINE_SIZE];
   int bytesread;
   LFILE *lf;
   taskpacket_t pack;
   int wsize;
     
   wsize = sizeof(taskpacket_t);
   lf = lopen(NULL,0);
   if (lf == NULL)
      fprintf(stderr, "Failed to open remote logger.\n");
   for( ; ; ) {
      bytesread =  readblock(STDIN_FILENO, &pack, wsize);
      if (bytesread == 0) {
         lprintf(lf, "End-of-file received\n");
         break; 
      }
      if (bytesread != wsize) {
         lprintf(lf, "Error reading packet header\n");
         return 1;
      }
      if ( (pack.type < 0) || (pack.type >= NUMTYPES) ) {
         fprintf(stderr, "Got invalid packet\n");
         return 1;
      }  
      lprintf(lf, "%s %s\n   compid = %d\n   taskid = %d\n   length = %d\n",
             "Received packet header of type",
             typename[pack.type], pack.compid, pack.taskid, pack.length);
      if (pack.length > MAX_PACK_SIZE) {
         lprintf(lf, "Task data is too long\n");
         return 1;
      }
      if (readblock(STDIN_FILENO, buf, pack.length) != pack.length) {
         lprintf(lf, "Error reading packet data\n");
         return 1;
      }
      lprintf(lf, buf, pack.length);
   }
   return 0;
}    
