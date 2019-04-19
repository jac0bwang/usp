#include <stdio.h>
#include <unistd.h>

#define BUFSIZE 80

int readline(int fd, char *buf, int nbytes);

int main(void) {
   char buf[BUFSIZE];
   int num;

   while ( (num = readline(STDIN_FILENO, buf, BUFSIZE)) > 0) {
      fprintf(stderr,"Number of bytes read: %d\n",num);
      fprintf(stderr,"Line:!%.*s!\n",num,buf);
   }
   if (num < 0) {
      fprintf(stderr,"readline returned %d\n",num);
      return 1;
   }
   return 0;
}
