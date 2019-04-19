#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "restart.h"
#define AUDIO_DEVICE "/dev/audio"
#define BLKSIZE 1024
 
int main(void) {
   int audiofd;
   char *bp;
   char buffer[BLKSIZE];
   unsigned bytesneeded;
   int bytesread;
 
   if ((audiofd = open(AUDIO_DEVICE, O_NONBLOCK | O_RDWR)) == -1) {
      perror("Failed to open audio device");
      return 1;
    }
 
    bp = buffer;
    bytesneeded = BLKSIZE;
    while(bytesneeded != 0) {
       bytesread = r_read(audiofd, bp, bytesneeded);
       if ((bytesread == -1) && (errno != EAGAIN))
          break;
       if (bytesread > 0) {
          bp += bytesread;
          bytesneeded -= bytesread;
       } 
    }
    fprintf(stderr, "%d bytes read\n", BLKSIZE - bytesneeded);
    return 0;
}
