#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define BUFSIZE 100
int setnoncanonical();
int gettermios(struct termios *termp);
int settermios(struct termios *termp);

int main() {
   char buf[BUFSIZE];
   struct termios term;
   int ret;

   fprintf(stderr,"Starting out in current mode\n");
   ret = read(STDIN_FILENO,buf,BUFSIZE);
   if (ret != -1)
      fprintf(stderr,"Got %d characters: !%.*s!\n",ret,ret,buf);
   if (gettermios(&term)) {
      perror("gettermios error");
      return 1;
   }
   fprintf(stderr,"Setting non-canonical mode\n");
   setnoncanonical();
   ret = read(STDIN_FILENO,buf,BUFSIZE);
   if (ret != -1)
      fprintf(stderr,"Got %d characters: !%.*s!\n",ret,ret,buf);
   fprintf(stderr,"Restoring mode\n");
   if (settermios(&term)) {
      perror("settermios error");
      return 1;
   }
   ret = read(STDIN_FILENO,buf,BUFSIZE);
   if (ret != -1)
      fprintf(stderr,"Got %d characters: !%.*s!\n",ret,ret,buf);
   return 0;
}
