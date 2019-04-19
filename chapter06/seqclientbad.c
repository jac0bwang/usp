#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "restart.h"
#define ERROR_CHAR 'e'
#define OK_CHAR 'g'
#define REPEAT_MAX 100
#define REQUEST_FIFO 1
#define SEQUENCE_FIFO 2
#define SLEEP_MAX 5

int main (int argc, char *argv[]) {
   int i;
   char reqbuf[1];  
   int reqfd, seqfd;             
   long seqnum;

   if (argc != 3) {            /* names of pipes are command-line arguments */
      fprintf(stderr, "Usage: %s requestfifo sequencefifo\n", argv[0]);
      return 1; 
   }
   if (((reqfd = open(argv[REQUEST_FIFO], O_WRONLY)) == -1) ||
       ((seqfd = open(argv[SEQUENCE_FIFO], O_RDONLY)) == -1)) {
       perror("Client failed to open a FIFO");
       return 1;
   }
   for (i = 0; i < REPEAT_MAX; i++) {
       reqbuf[0] = OK_CHAR;
       sleep((int)(SLEEP_MAX*drand48()));
       if (r_write(reqfd, reqbuf, 1) == -1) {
          perror("Client failed to write request");
          break;
       }
       if (r_read(seqfd, &seqnum, sizeof(seqnum)) != sizeof(seqnum) ) {
           fprintf(stderr, "Client failed to read full sequence number\n");
           reqbuf[0] = ERROR_CHAR;
           r_write(reqfd, reqbuf, 1); 
           break;
       }
       fprintf(stderr, "[%ld]:received sequence number %ld\n", 
               (long)getpid(), seqnum);
    }
   return 0; 
}
