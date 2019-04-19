#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "restart.h"

int ttysetchar(int fd, int flagname, char c);

int setnoncanonical(void) { 
   int error;
   int fd;
   int firsterrno = 0;
   struct termios term;
   char termbuf[L_ctermid];
             
   if (ctermid(termbuf) == NULL) {               /* find the terminal name */
      errno = ENODEV;
      return -1;
   }
   if ((fd = r_open2(termbuf, O_RDONLY)) == -1)       /* open the terminal */
      return -1;
   if (tcgetattr(fd, &term) == -1)                      /* get its termios */
      firsterrno = errno;
   else {
      term.c_lflag &= ~ICANON;     
      while (((error = tcsetattr(fd, TCSAFLUSH, &term)) == -1) &&
              (errno == EINTR)) ;
      if (error)
         firsterrno = errno;
   }
   if (!firsterrno && (ttysetchar(fd, VMIN, 1) || ttysetchar(fd, VTIME, 0)))
      firsterrno = errno;
   if ((r_close(fd) == -1) && !firsterrno)
      firsterrno = errno;
   if (firsterrno)
      errno = firsterrno;
   return firsterrno ? -1 : 0;
}
