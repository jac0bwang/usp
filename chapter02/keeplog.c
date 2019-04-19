#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MAX_CANON
#define MAX_CANON 8192
#endif   

int runproc(char *cmd);
void showhistory(FILE *f);

int main(int argc, char *argv[]) {
   char cmd[MAX_CANON];
   int history = 1;

   if (argc == 1)
      history = 0;
   else if ((argc > 2) || strcmp(argv[1], "history")) {
      fprintf(stderr, "Usage: %s [history]\n", argv[0]);
      return 1; 
   }   
   while(fgets(cmd, MAX_CANON, stdin) != NULL) {
      if (*(cmd + strlen(cmd) - 1) == '\n')
          *(cmd + strlen(cmd) - 1) = 0;
      if (history && !strcmp(cmd, "history"))
         showhistory(stdout);
      else if (runproc(cmd)) {
         perror("Failed to execute command");
         break;
      }
   }  
   printf("\n\n>>>>>>The list of commands executed is:\n");
   showhistory(stdout);
   return 0; 
}
