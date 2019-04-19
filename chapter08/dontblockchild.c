#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
   pid_t child;
   sigset_t mask, omask;

/*
   if ((sigfillset(&mask) == -1) || 
        (sigprocmask(SIG_SETMASK, &mask, &omask) == -1)) {
      perror("Couldn't block the signals");
      return 1;
   }
*/
   if ((child = fork()) == -1) {
      perror("Could not fork child");
      return 1;
   } 
   if (child == 0) {                         /* child code */
      execl("/bin/ls", "ls", "-l", NULL); 
      perror("Exec failed");
      return 1; 
   }
/*
   if (sigprocmask(SIG_SETMASK, &omask, NULL) == -1){
      perror("Parent could not restore signal mask");
      return 1;
   }
*/
   while (wait(NULL) == -1)
      if (errno != EINTR) {
         perror("Parent error waiting for child");
         return 1;
      }
   return 0;
}
