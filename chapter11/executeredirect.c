#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int makeargv(const char *s, const char *delimiters, char ***argvp);
int parseandredirectin(char *s);
int parseandredirectout(char *s);

void executeredirect(char *s, int in, int out) {
   char **chargv;
   char *pin;
   char *pout;

   if (in && ((pin = strchr(s, '<')) != NULL) && 
       out && ((pout = strchr(s, '>')) != NULL) && (pin > pout) ) {
      if (parseandredirectin(s) == -1) { /* redirect input is last on line */
         perror("Failed to redirect input");
         return;
      }
      in = 0;
   }
   if (out && (parseandredirectout(s) == -1))
      perror("Failed to redirect output");
   else if (in && (parseandredirectin(s) == -1))
      perror("Failed to redirect input");
   else if (makeargv(s, " \t", &chargv) <= 0)
      fprintf(stderr,"Failed to parse command line\n");
   else {
      execvp(chargv[0], chargv);
      perror("Failed to execute command");
   }
   exit(1);
}
