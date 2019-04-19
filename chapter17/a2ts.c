#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "restart.h"
#include "ntpvm.h"
#define MAX_LINE_SIZE 100
#define TERMINATE_STRING "!!!!!\n"

static char *typename[] = {"Start Task", "Data", "Broadcast", "Done",
                         "Terminate", "Barrier"};

int main(void)  {
   char buf[MAX_PACK_SIZE + MAX_LINE_SIZE];
   char *bufptr;
   int i;
   int linelen;
   taskpacket_t pack;
   int tasktype;    
   int wsize;  
 
   wsize = sizeof(taskpacket_t);
   fprintf(stderr, "Ready for first packet\n");
   for( ; ; ) {                       /* loop with menu for interactive input */ 
      fprintf(stderr, "Enter compid:");
      if (scanf("%d", &pack.compid) == EOF) 
         break;
      fprintf(stderr, "Enter taskid:");
      scanf("%d", &pack.taskid);
      fprintf(stderr, "Enter task type:\n");
      for (i=0; i< NUMTYPES; i++)
         fprintf(stderr, "   %d = %s\n", i, typename[i]);
      scanf("%d", &tasktype);
      pack.type = tasktype;
      pack.length = 0;
      bufptr = buf;
      *bufptr = 0;
      fprintf(stderr, "Enter first line of data (%.*s to end):\n",
         strlen(TERMINATE_STRING) - 1, TERMINATE_STRING);
 
      while ((linelen = readline(STDIN_FILENO, bufptr, MAX_LINE_SIZE)) != -1) {
         if (linelen == 0)
            break;
         if (strcmp(TERMINATE_STRING, bufptr) == 0)
            break;
         bufptr = bufptr + linelen;
         pack.length = pack.length + linelen;
         if (pack.length >= MAX_PACK_SIZE) {
            fprintf(stderr, "**** Maximum packet size exceeded\n");
            return 1;
         }
         fprintf(stderr, "Received %d, total=%d, Enter line (%.*s to end):\n",
             linelen, pack.length, strlen(TERMINATE_STRING) - 1,
             TERMINATE_STRING);
      } 
      fprintf(stderr, "Writing packet header: %d %d %d %d\n",
          pack.compid, pack.taskid, (int)pack.type, pack.length);
      if (write(STDOUT_FILENO, &pack, wsize) != wsize) {
         fprintf(stderr, "Error writing packet\n");
         return 1;
      } 
      fprintf(stderr, "Writing %d bytes\n", pack.length);
      if (write(STDOUT_FILENO, buf, pack.length) != pack.length) {
         fprintf(stderr,"Error writing packet\n");
         return 1;
      } 
      fprintf(stderr, "Ready for next packet\n");
   }    
   fprintf(stderr, "a2ts exiting normally\n");
   return 0;
}
