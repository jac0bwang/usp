#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include "doneflag.h"
#include "globalerror.h"

static int signalnum = 0;

/* ARGSUSED */
static void *signalthread(void *arg) {    /* dedicated to handling signalnum */
   int error;
   sigset_t intmask;
   struct sched_param param;
   int policy;
   int sig;
 
   if (error = pthread_getschedparam(pthread_self(), &policy, &param)) {  
      seterror(error);
      return NULL;
   }
   fprintf(stderr, "Signal thread entered with policy %d and priority %d\n",
              policy,  param.sched_priority);
   if ((sigemptyset(&intmask) == -1) ||
       (sigaddset(&intmask, signalnum) == -1) ||
       (sigwait(&intmask, &sig) == -1))
      seterror(errno);
   else 
      seterror(setdone());
   return NULL;
}

int signalthreadinit(int signo) {
   int error;
   pthread_attr_t highprio;
   struct sched_param param;
   int policy;
   sigset_t set;
   pthread_t sighandid;
   
   signalnum = signo;                                    /* block the signal */
   if ((sigemptyset(&set) == -1) || (sigaddset(&set, signalnum) == -1) ||
      (sigprocmask(SIG_BLOCK, &set, NULL) == -1))
      return errno;
   if ( (error = pthread_attr_init(&highprio)) ||    /* with higher priority */
        (error = pthread_attr_getschedparam(&highprio, &param)) ||
        (error = pthread_attr_getschedpolicy(&highprio, &policy)) )
      return error;
   if (param.sched_priority < sched_get_priority_max(policy)) {
      param.sched_priority++;
      if (error = pthread_attr_setschedparam(&highprio, &param))
         return error;
   } else 
     fprintf(stderr, "Warning, cannot increase priority of signal thread.\n");
   if (error = pthread_create(&sighandid, &highprio, signalthread, NULL))
      return error;
   return 0;
}
