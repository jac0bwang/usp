#include <unistd.h>
#include "restart.h"
#define BLKSIZE 1024

int copyfile(int fromfd, int tofd) {
   char buf[BLKSIZE]; 
   int bytesread, byteswritten;
   int totalbytes = 0;

   for (  ;  ;  ) {
      if ((bytesread = r_read(fromfd, buf, BLKSIZE)) <= 0)
         break;     
      if ((byteswritten = r_write(tofd, buf, bytesread)) == -1)
         break;
      totalbytes += byteswritten;
   }
   return totalbytes;
}
