#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int makeargv(const char *s, const char *delimiters, char ***argvp);
int parseandredirectin(char *s);
int parseandredirectout(char *s);

void executecmd(char *incmd) {
   char **chargv;
   if (parseandredirectout(incmd) == -1)
      perror("Failed to redirect output");
   else if (parseandredirectin(incmd) == -1)
      perror("Failed to redirect input");
   else if (makeargv(incmd, " \t", &chargv) <= 0)
      fprintf(stderr, "Failed to parse command line\n");
   else {
      execvp(chargv[0], chargv);
      perror("Failed to execute command");
   }
   exit(1);
}
