#include <aio.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include "asyncmonitorpoll.h"
#define BLKSIZE 1024                            /* size of blocks to be read */

typedef struct {
   char buf[BLKSIZE];
   ssize_t bytes;
   struct aiocb control;       
   int doneflag;
   int startedflag;
} aio_t;

static aio_t iops[NUMOPS];                         /* information for the op */
 
/* -------------------------- Public Functions ----------------------------- */
int initaio(int fd, int handle)       {          /* set up control structure */
   if (handle >= NUMOPS) {
      errno = EINVAL;
      return -1;
   }
   iops[handle].control.aio_fildes = fd;              /* I/O operation on fd */
   iops[handle].control.aio_offset = 0;
   iops[handle].control.aio_buf = (void *)iops[handle].buf;
   iops[handle].control.aio_nbytes = BLKSIZE;
   iops[handle].control.aio_sigevent.sigev_notify = SIGEV_NONE;
   iops[handle].doneflag = 0;
   iops[handle].startedflag = 0;  
   iops[handle].bytes = 0;
   return 0;
} 

/* return -1 if not done or error
             errno = EINPROGRESS if not done
   otherwise, return number of bytes read with *buf pointing to buffer
*/
int readcheck(int handle, char **bufp) {   /* see if read for handle is done */ 
   int error;
   ssize_t numbytes;
   struct aiocb *thisp;

   thisp = &(iops[handle].control);            /* get a pointer to the aiocp */
   if (iops[handle].doneflag) {       /* done already, don't call aio_return */
      numbytes = iops[handle].bytes;
      *bufp = (char *)iops[handle].control.aio_buf; /* set pointer to buffer */
      return numbytes;
   }
   error = aio_error(thisp);
   if (error) {
      errno = error;
      return -1;
   }
   numbytes = aio_return(thisp);
   iops[handle].bytes = numbytes;
   *bufp = (char *)iops[handle].control.aio_buf;    /* set pointer to buffer */
   iops[handle].control.aio_offset += numbytes;             /* update offset */
   iops[handle].doneflag = 1;
   return numbytes;
}

int readstart(int handle) {    /* start read for I/O corresponding to handle */
   int error;
   struct aiocb *thisp;

   thisp = &(iops[handle].control);            /* get a pointer to the aiocp */
   if (iops[handle].startedflag) {                        /* already started */
      errno = EINVAL;
      return -1;
   }
   if ((error = aio_read(thisp)) == -1) {
      errno = error;
      return -1;
   }
   iops[handle].startedflag = 1;
   return 0;
}

void reinit(int handle) {   /* must be called before doing another readstart */
   iops[handle].doneflag = 0;
   iops[handle].startedflag = 0;  
   iops[handle].bytes = 0;
}
