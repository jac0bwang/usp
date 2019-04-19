#include <limits.h>
#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BACK_SYMBOL '&'
#define PROMPT_STRING "ush6>>"
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
   char *backp;
   sigset_t blockmask;
   pid_t childpid;
   struct sigaction defhandler;
   int inbackground;
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
      okaytojump = 1;
      printf("%d",(int)getpid());
      if (fputs(PROMPT_STRING, stdout) == EOF)
          continue;
      if (fgets(inbuf, MAX_CANON, stdin) == NULL)
          continue;
      len = strlen(inbuf);
      if (inbuf[len - 1] == '\n')
          inbuf[len - 1] = 0;
      if (strcmp(inbuf, QUIT_STRING) == 0)
          break;
      if ((backp = strchr(inbuf, BACK_SYMBOL)) == NULL)
          inbackground = 0;
      else {
         inbackground = 1; 
         *backp = 0;
      }
      if (sigprocmask(SIG_BLOCK, &blockmask, NULL) == -1)
         perror("Failed to block signals");
      if ((childpid = fork()) == -1)
          perror("Failed to fork");
      else if (childpid == 0) {
         if (inbackground) {             /* child creates another process */
             if ((childpid = fork()) == -1) {
                perror("Second fork failed"); 
                return 1;
             }
             if (childpid > 0)
                return 0;
             if (setpgid(0, 0) == -1) {
                perror("setpgod failed");
                return 1;
             }
         }
         if ((sigaction(SIGINT, &defhandler, NULL) < 0) ||
             (sigaction(SIGQUIT, &defhandler, NULL) < 0) || 
             (sigprocmask(SIG_UNBLOCK, &blockmask, NULL) == -1)) {
             perror("Failed to set signal handling for command "); 
             return 1; 
         }
         executecmd(inbuf);
         perror("Failed to execute command");
         return 1;
      }
      if (sigprocmask(SIG_UNBLOCK, &blockmask, NULL) == -1)
         perror("Failed to unblock signals");
      wait(NULL);
   }
   return 0;
}
