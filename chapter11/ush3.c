#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define PROMPT_STRING "ush3>>"
#define QUIT_STRING "q"

void executecmd(char *incmd);
int signalsetup(struct sigaction *def, sigset_t *mask, void (*handler)(int));

int main (void) {
   sigset_t blockmask;
   pid_t childpid;
   struct sigaction defaction;
   char inbuf[MAX_CANON];
   int len;

   if (signalsetup(&defaction, &blockmask, SIG_IGN) == -1) {
      perror("Failed to set up shell signal handling");
      return 1;
   }
   if (sigprocmask(SIG_BLOCK, &blockmask, NULL) == -1) {
      perror("Failed to block signals");
      return 1;
   }

   for( ; ; ) {
      if (fputs(PROMPT_STRING, stdout) == EOF)
          continue;
      if (fgets(inbuf, MAX_CANON, stdin) == NULL)
          continue;
      len = strlen(inbuf);
      if (inbuf[len - 1] == '\n')
         inbuf[len - 1] = 0;
      if (strcmp(inbuf, QUIT_STRING) == 0)
          break;
      if ((childpid = fork()) == -1) {
          perror("Failed to fork child to execute command");
      } else if (childpid == 0) {
          if ((sigaction(SIGINT, &defaction, NULL) == -1) ||
              (sigaction(SIGQUIT, &defaction, NULL) == -1) ||
              (sigprocmask(SIG_UNBLOCK, &blockmask, NULL) == -1)) {
              perror("Failed to set signal handling for command "); 
              return 1; 
          }
          executecmd(inbuf);
          return 1;
      } 
      wait(NULL);
   }
   return 0;
}
