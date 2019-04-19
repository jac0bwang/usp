#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "restart.h"

int setecho(int fd, int onflag);

int password(const char *prompt, char *passbuf, int passmax) { 
    int fd;
    int firsterrno = 0;  
    sigset_t signew, sigold;
    char termbuf[L_ctermid];

    if (ctermid(termbuf) == NULL) {                 /* find the terminal name */
       errno = ENODEV;
       return -1;
    }
    if ((fd = open(termbuf, O_RDONLY)) == -1)  /* open descriptor to terminal */
       return -1;
    if ((sigemptyset(&signew) == -1) ||  /* block SIGINT, SIGQUIT and SIGTSTP */
        (sigaddset(&signew, SIGINT) == -1) || 
        (sigaddset(&signew, SIGQUIT) == -1) || 
        (sigaddset(&signew, SIGTSTP) == -1) ||
        (sigprocmask(SIG_BLOCK, &signew, &sigold) == -1) || 
        (setecho(fd, 0) == -1)) {                    /* set terminal echo off */
         firsterrno = errno;
       sigprocmask(SIG_SETMASK, &sigold, NULL);
       r_close(fd);
       errno = firsterrno;
       return -1;
    }
    if ((r_write(STDOUT_FILENO, (char *)prompt, strlen(prompt)) == -1) ||
        (readline(fd, passbuf, passmax) == -1))              /* read password */
        firsterrno = errno;
    else
       passbuf[strlen(passbuf) - 1] = 0;                    /* remove newline */
    if ((setecho(fd, 1) == -1) && !firsterrno)           /* turn echo back on */
       firsterrno = errno;
    if ((sigprocmask(SIG_SETMASK, &sigold, NULL) == -1) && !firsterrno )
       firsterrno = errno;
    if ((r_close(fd) == -1) && !firsterrno)   /* close descriptor to terminal */
       firsterrno = errno;
    return firsterrno ? errno = firsterrno, -1: 0;
}
