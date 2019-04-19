#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

pthread_attr_t *makepriority(int priority);

/* ARGSUSED */
static void *showthread(void *arg) {
   int error;
   struct sched_param param;
   int policy;

   if (error = pthread_getschedparam(pthread_self(), &policy, &param)) {
      fprintf(stderr,"getparam error: %s",strerror(error));
      return NULL;
   }
   fprintf(stderr, "Thread entered with policy %d and priority %d\n",
              policy,  param.sched_priority);
   return NULL;
}


int main(void) {
   pthread_t tid;
   pthread_attr_t *attrp;

   if (pthread_create(&tid, NULL, showthread, NULL))
      fprintf(stderr,"error creating first thread\n");
   sleep(1);
   attrp = makepriority(10);
   if (attrp == NULL)
      perror("making attribute");
   if (pthread_create(&tid, attrp, showthread, NULL))
      fprintf(stderr,"error creating second thread\n");
   sleep(1);
   return 0;
}
