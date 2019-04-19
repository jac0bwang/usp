#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "restart.h"

int gettermios(struct termios *termp) { 
   int fd;
   int firsterrno = 0;
   char termbuf[L_ctermid];
             
   if (ctermid(termbuf) == NULL) {                /* find the terminal name */
      errno = ENODEV;
      return -1;
   }
   if ((fd = r_open2(termbuf, O_RDONLY)) == -1)        /* open the terminal */
      return -1;
   if (tcgetattr(fd, termp) == -1)                       /* get its termios */
      firsterrno = errno;
   if ((r_close(fd) == -1) && !firsterrno)
      firsterrno = errno;
   if (firsterrno) {
      errno = firsterrno;
      return -1;
   }
   return 0;
}

int settermios(struct termios *termp) { 
   int error;
   int fd;
   int firsterrno = 0;
   char termbuf[L_ctermid];
   
   if (ctermid(termbuf) == NULL) {                /* find the terminal name */
      errno = ENODEV;
      return -1;
   }
   if ((fd = r_open2(termbuf, O_RDONLY)) == -1)        /* open the terminal */
      return -1;
   while (((error = tcsetattr(fd, TCSAFLUSH, termp)) == -1) && 
           (errno == EINTR)) ;
   if (error)
      firsterrno = errno;
   if ((r_close(fd) == -1) && !firsterrno)
      firsterrno = errno;
   if (firsterrno) {
      errno = firsterrno;
      return -1;
   }
   return 0;
}
