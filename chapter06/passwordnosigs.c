#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "restart.h"

int readline(int fd, char *buf, int nbytes);
int setecho(int fd, int onflag);

int passwordnosigs(char *prompt, char *passbuf, int passmax) { 
   int fd;
   int firsterrno = 0;
   int passlen;
   char termbuf[L_ctermid];
             
   if (ctermid(termbuf) == NULL) {               /* find the terminal name */
      errno = ENODEV;
      return -1;
   }
   if ((fd = r_open2(termbuf, O_RDWR)) == -1)         /* open the terminal */
      return -1;
   if (setecho(fd, 0) == -1)                              /* turn echo off */
      firsterrno = errno;
   else if (r_write(fd, prompt, strlen(prompt)) == -1)     /* write prompt */
      firsterrno = errno;
   else if ((passlen = readline(fd, passbuf, passmax)) == 0)
      firsterrno = EINVAL;
   else if (passlen == -1)
      firsterrno = errno;
   else
      passbuf[passlen-1] = '\0';                         /* remove newline */
   if ((setecho(fd, 1) == -1) && !firsterrno)  /* always turn echo back on */
      firsterrno =  errno;
   if ((r_write(fd,"\n",1) == -1) && !firsterrno)
      firsterrno = errno;
   if ((r_close(fd) == -1) && !firsterrno)
      firsterrno = errno;
   if (firsterrno)
      errno = firsterrno;
   return firsterrno ? -1 : 0;
}
