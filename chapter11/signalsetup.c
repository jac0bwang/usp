#include <signal.h>
#include <stdio.h>

int signalsetup(struct sigaction *def, sigset_t *mask, void (*handler)(int)) {
   struct sigaction catch;

   catch.sa_handler = handler;  /* Set up signal structures  */
   def->sa_handler = SIG_DFL;
   catch.sa_flags = 0;    
   def->sa_flags = 0;   
   if ((sigemptyset(&(def->sa_mask)) == -1) || 
       (sigemptyset(&(catch.sa_mask)) == -1) || 
       (sigaddset(&(catch.sa_mask), SIGINT) == -1) || 
       (sigaddset(&(catch.sa_mask), SIGQUIT) == -1) || 
       (sigaction(SIGINT, &catch, NULL) == -1) || 
       (sigaction(SIGQUIT, &catch, NULL) == -1) || 
       (sigemptyset(mask) == -1) || 
       (sigaddset(mask, SIGINT) == -1) || 
       (sigaddset(mask, SIGQUIT) == -1))
       return -1;  
    return 0;  
}
