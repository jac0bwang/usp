#include <errno.h>
#include <unistd.h>

ssize_t readblock(int fd, void *buf, size_t size) {
   char *bufp;
   size_t bytestoread;
   ssize_t bytesread;
   size_t totalbytes;

   for (bufp = buf, bytestoread = size, totalbytes = 0;
        bytestoread > 0;
        bufp += bytesread, bytestoread -= bytesread) {
      bytesread = read(fd, bufp, bytestoread);
      if ((bytesread == 0) && (totalbytes == 0))
         return 0;
      if (bytesread == 0) { 
         errno = EINVAL; 
         return -1;    
      } 
      if ((bytesread) == -1 && (errno != EINTR))
         return -1;
      if (bytesread == -1)
         bytesread = 0;
      totalbytes += bytesread;
   }
   return totalbytes;
}
