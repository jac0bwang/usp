#include <limits.h>
#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define PROMPT_STRING "ush4>>"
#define QUIT_STRING "q"

void executecmd(char *incmd);
int signalsetup(struct sigaction *def, sigset_t *mask, void (*handler)(int));
static sigjmp_buf jumptoprompt;
static volatile sig_atomic_t okaytojump = 0;

/* ARGSUSED */
static void jumphd(int signalnum) {
   if (!okaytojump) return;
   okaytojump = 0;
   siglongjmp(jumptoprompt, 1);
}

int main (void) {
   sigset_t blockmask;
   pid_t childpid;
   struct sigaction defhandler;
   int len;
   char inbuf[MAX_CANON];

   if (signalsetup(&defhandler, &blockmask, jumphd) == -1) {
      perror("Failed to set up shell signal handling");
      return 1;
   }

   for( ; ; ) {
       if ((sigsetjmp(jumptoprompt, 1)) &&   /* if return from signal, \n */
          (fputs("\n", stdout) == EOF) )
          continue;
      wait(NULL);
      okaytojump = 1;
      if (fputs(PROMPT_STRING, stdout) == EOF)
          continue;
      if (fgets(inbuf, MAX_CANON, stdin) == NULL)
          continue;
      len = strlen(inbuf);
      if (inbuf[len - 1] == '\n')
          inbuf[len - 1] = 0;
      if (strcmp(inbuf, QUIT_STRING) == 0)
          break;
      if (sigprocmask(SIG_BLOCK, &blockmask, NULL) == -1) 
         perror("Failed to block signals");
      if ((childpid = fork()) == -1) 
         perror("Failed to fork");
      else if (childpid == 0) {
         if ((sigaction(SIGINT, &defhandler, NULL) == -1) ||
             (sigaction(SIGQUIT, &defhandler, NULL) == -1) ||
             (sigprocmask(SIG_UNBLOCK, &blockmask, NULL) == -1)) {
             perror("Failed to set signal handling for command "); 
             return 1; 
         }
         executecmd(inbuf);
         return 1;
      }
      if (sigprocmask(SIG_UNBLOCK, &blockmask, NULL) == -1) 
         perror("Failed to unblock signals");
   }
   return 0;
}
