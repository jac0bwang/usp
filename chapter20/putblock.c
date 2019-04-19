#include <errno.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <sys/stat.h>
#include "restart.h"
#define BLKSIZE 8192
#define PUTBLOCK_PERMS (S_IRUSR | S_IWUSR)
 
int putblock(char *fname, int blknum, char *data) { 
  int error = 0;
  int file;

  if ((file = open(fname, O_WRONLY|O_CREAT, PUTBLOCK_PERMS)) == -1) 
     return -1; 
  if (lseek(file, blknum*BLKSIZE, SEEK_SET) == -1)
     error = errno;
  else if (r_write(file, data, BLKSIZE) == -1)
     error = errno;
  if ((r_close(file) == -1) && !error)
     error = errno;
  if (!error)
     return 0;
  errno = error;
  return -1; 
}

