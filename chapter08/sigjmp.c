#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static sigjmp_buf jmpbuf;
static volatile sig_atomic_t jumpok = 0;

/* ARGSUSED */
static void chandler(int signo) {
   if (jumpok == 0) return;
   siglongjmp(jmpbuf, 1);
}

int main(void)  {
   struct sigaction act;

   act.sa_flags = 0;
   act.sa_handler = chandler;
   if ((sigemptyset(&act.sa_mask) == -1) ||
       (sigaction(SIGINT, &act, NULL) == -1)) {
      perror("Failed to set up SIGINT handler");
      return 1; 
   }
                                                  /* stuff goes here */
   fprintf(stderr, "This is process %ld\n", (long)getpid());
   if (sigsetjmp(jmpbuf, 1))
      fprintf(stderr, "Returned to main loop due to ^c\n");
   jumpok = 1;
   for ( ; ; ) 
      ;                                       /* main loop goes here */
}
