#include <pthread.h>
#include <stdio.h>

int initbarrier(int n);
int waitbarrier();


/* ARGSUSED */
static void *printthread(void *arg) {
   fprintf(stderr,"This is the first print of thread %d\n",
                   (int)pthread_self());
   waitbarrier();
   fprintf(stderr,"This is the second print of thread %d\n",
                   (int)pthread_self());
   return NULL;
}

int main(void) {
   pthread_t t0,t1,t2;

   if (initbarrier(3)) {
      fprintf(stderr,"Error initilizing barrier\n");
      return 1;
   }
   if (pthread_create(&t0,NULL,printthread,NULL))
      fprintf(stderr,"Error creating thread 0.\n");
   if (pthread_create(&t1,NULL,printthread,NULL))
      fprintf(stderr,"Error creating thread 1.\n");
   if (pthread_create(&t2,NULL,printthread,NULL))
      fprintf(stderr,"Error creating thread 2.\n");
   if (pthread_join(t0,NULL))
      fprintf(stderr,"Error joining thread 0.\n");
   if (pthread_join(t1,NULL))
      fprintf(stderr,"Error joining thread 1.\n");
   if (pthread_join(t2,NULL))
      fprintf(stderr,"Error joining thread 2.\n");
   fprintf(stderr,"All threads complete.\n");
   return 0;
}
   
