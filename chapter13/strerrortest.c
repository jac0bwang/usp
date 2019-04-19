#include <pthread.h>
#include <stdio.h>
#define BUFSIZE 256

int strerror_r(int errnum, char *strerrbuf, size_t buflen);

/* ARGSUSED */
static void *printthread(void *arg) {
   int n;
   char buf[BUFSIZE];
   int i;

   n = *((int *)arg);
   
   for (i=0; i<10; i++) {
      if (strerror_r(n, buf, BUFSIZE))
         fprintf(stderr, "Error in call to strerror_r\n");
      fprintf(stderr,"This is thread %d with error %s\n", n, buf);
   }
   return NULL;
}

int main(void) {
   pthread_t t0,t1,t2;
   int val0 = 1;
   int val1 = 2;
   int val2 = 3;

   if (pthread_create(&t0,NULL,printthread,&val0))
      fprintf(stderr,"Error creating thread 0.\n");
   if (pthread_create(&t1,NULL,printthread,&val1))
      fprintf(stderr,"Error creating thread 1.\n");
   if (pthread_create(&t2,NULL,printthread,&val2))
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
   
