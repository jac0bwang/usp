#include <errno.h> 
#include <termios.h> 
#include <unistd.h>

int ttysetchar(int fd, int flagname, char c)  {
   int error;
   struct termios term;
   
   if (tcgetattr(fd, &term) == -1) 
      return -1;
   term.c_cc[flagname] = (cc_t)c; 
   while (((error = tcsetattr(fd, TCSAFLUSH, &term)) == -1) &&
           (errno == EINTR)) ;
   return error;
}   
