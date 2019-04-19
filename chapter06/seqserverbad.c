#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "restart.h"
#define ERROR_CHAR 'e'
#define OK_CHAR 'g'
#define REQUEST_FIFO 1
#define REQ_PERMS (S_IRUSR | S_IWUSR | S_IWGRP | S_IWOTH)
#define SEQUENCE_FIFO 2
#define SEQ_PERMS (S_IRUSR | S_IWUSR | S_IRGRP| S_IROTH)

int main (int argc, char *argv[]) {
   char buf[1]; 
   int reqfd, seqfd;            
   long seqnum = 1;
   if (argc != 3) {            /* names of fifos passed on the command line */
      fprintf(stderr, "Usage: %s requestfifo sequencefifo\n", argv[0]);
      return 1; 
   }
                         /* create a named pipe to handle incoming requests */
   if ((mkfifo(argv[REQUEST_FIFO], REQ_PERMS) == -1) && (errno != EEXIST)) {
       perror("Server failed to create request FIFO");
       return 1; 
   }
   if ((mkfifo(argv[SEQUENCE_FIFO], SEQ_PERMS) == -1) && (errno != EEXIST)){
       perror("Server failed to create sequence FIFO");
       if (unlink(argv[REQUEST_FIFO]) == -1)
          perror("Server failed to unlink request FIFO");
       return 1; 
   }
   if (((reqfd = open(argv[REQUEST_FIFO], O_RDWR)) == -1) || 
       ((seqfd = open(argv[SEQUENCE_FIFO], O_RDWR)) == -1)) {
      perror("Server failed to open one of the FIFOs");
      return 1;
   }
   for ( ;  ;  ) {
      if (r_read(reqfd, buf, 1) == 1) {
         if ((buf[0] == OK_CHAR) &&
             (r_write(seqfd, &seqnum, sizeof(seqnum)) == sizeof(seqnum)))
            seqnum++;
         else if (buf[0] == ERROR_CHAR) 
            break;
      }
   }
   if (unlink(argv[REQUEST_FIFO]) == -1)
      perror("Server failed to unlink request FIFO");
   if (unlink(argv[SEQUENCE_FIFO]) == -1)
      perror("Server failed to unlink sequence FIFO");
   return 0;
}
