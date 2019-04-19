#include "restart.h"

int readwriteblock(int fromfd, int tofd, char *buf, int size) {
   int bytesread;

   bytesread = readblock(fromfd, buf, size);
   if (bytesread != size)                      /* can only be 0 or -1 */
      return bytesread;
   return r_write(tofd, buf, size);
}
