#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "restart.h"
#include "uici.h"
int copyfile(int fromfd, int tofd);

int hasvoice(char *audio_buffer, int length);

#define BLKSIZE 1024

int read_and_write(int fromfd, int tofd) {
   char buf[BLKSIZE];
   int bytes_read;

   if ((bytes_read = r_read(fromfd, buf, BLKSIZE)) < 0) 
      return -1;
   else if (bytes_read == 0)
      return 0;
   else if (hasvoice(buf,bytes_read)) {
      if (r_write(tofd, buf, bytes_read) < 0)
         return -1;
   }
   return bytes_read;
}

int main(int argc, char *argv[])
{
   int bytes_copied;
   int communfd;
   u_port_t portnumber;
 
   if (argc != 3) {
      fprintf(stderr, "Usage: %s host port\n", argv[0]);
      return 1;
   }
   portnumber = (u_port_t)atoi(argv[2]);
   if ((communfd = u_connect(portnumber, argv[1])) < 0) {
      perror("Connection failed");
      return 1;
   }
   fprintf(stderr, "[%ld]: A connection has been made to %s\n",
                    (long)getpid(), argv[1]);
   bytes_copied = copyfile(STDIN_FILENO, communfd);
   close(communfd);
   fprintf(stderr, "[%ld]:Bytes sent = %d\n", (long) getpid(), bytes_copied);
   return 0;
}
