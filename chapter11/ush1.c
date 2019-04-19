#include <stdio.h> 
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_BUFFER 256
#define QUIT_STRING "q"

int makeargv(const char *s, const char *delimiters, char ***argvp);
 
int main (void) {
   char **chargv;
   char inbuf[MAX_BUFFER];
 
   for( ; ; ) {
      gets(inbuf);
      if (strcmp(inbuf, QUIT_STRING) == 0)
         return 0;
      if ((fork() == 0) && (makeargv(inbuf, " ", &chargv) > 0))
         execvp(chargv[0], chargv);
      wait(NULL);
   }
}
