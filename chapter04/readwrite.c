#include <limits.h>
#include "restart.h"
#define BLKSIZE PIPE_BUF

int readwrite(int fromfd, int tofd) {
   char buf[BLKSIZE];
   int bytesread;

   if ((bytesread = r_read(fromfd, buf, BLKSIZE)) == -1)
      return -1;
   if (bytesread == 0)
      return 0;
   if (r_write(tofd, buf, bytesread) == -1)
      return -1;
   return bytesread;
}
