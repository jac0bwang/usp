#include <errno.h>
#include <unistd.h>

int r_close(int fd) {
   int retval;

   while (retval = close(fd), retval == -1 && errno == EINTR) ;
   return retval;
}
