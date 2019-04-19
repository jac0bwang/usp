#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

int increment();
int decrement();
int getcount(int *thecount);
int wastetime(int numus);

/* return 1 on failure */
static int waste_random_time(int maxus) {
   int i;
   int numus;
   struct timeval tp1;

   if (gettimeofday(&tp1,NULL) != 0) {
       fprintf(stderr,"error in gettimeofday\n");
       return 1;
   }
   srand48((long)tp1.tv_usec);
   for (i = 0; i<100; i++)
      (void)drand48();
   numus = (int)(drand48()*maxus);

   return wastetime(numus);
}


static void *incthread(void *arg) {
   int num;
   int i;
   char c;
   num = *(int *)arg;
   fprintf(stderr,"incthread started: %d\n",num);
   for (i=0;i<num;i++) {
      increment();
      waste_random_time(4000);
      read(0,&c,1);
   }
   fprintf(stderr,"incthread done\n");
   return NULL;
}

static void *decthread(void *arg) {
   int num;
   int i;
   char c;
   num = *(int *)arg;
   fprintf(stderr,"decthread started: %d\n",num);
   for (i=0;i<num;i++) {
      decrement();
      waste_random_time(4000);
      read(0,&c,1);
   }
   fprintf(stderr,"decthread done\n");
   return NULL;
}

/* ARGSUSED */
static void *showcount(void *arg) {
   int count_now;
   int error;

   for ( ; ; ) {
      if (error = getcount(&count_now)) {
         fprintf(stderr,"Error getting count: %s\n",strerror(error));

         break;
      }
      fprintf(stderr,"Count is %d\n",count_now);
      sleep(1);
   }
   return NULL;
}


int main(void) {
   pthread_t t0,t1,t2,t3,t4;
   int error;
   int num = 10;
   int num1 = 10;
   int count_now;

   fprintf(stderr,"Run this and push return 40 times\n");
   fprintf(stderr,"Each push wil cause either an inc or dec\n");
   fprintf(stderr,"After 40 returns, the total count should be 0\n");
   fprintf(stderr,"Creating 0\n");
   if (error = pthread_create(&t0,NULL,showcount,&num))
      fprintf(stderr,"Error creating thread 0: %s\n",strerror(error));
   fprintf(stderr,"Creating 1\n");
   if (error = pthread_create(&t1,NULL,incthread,&num))
      fprintf(stderr,"Error creating thread 1: %s\n",strerror(error));
   fprintf(stderr,"Creating 2\n");
   if (error = pthread_create(&t2,NULL,decthread,&num1))
      fprintf(stderr,"Error creating thread 2: %s\n",strerror(error));
   fprintf(stderr,"Creating 3\n");
   if (error = pthread_create(&t3,NULL,incthread,&num))
      fprintf(stderr,"Error creating thread 3: %s\n",strerror(error));
   fprintf(stderr,"Creating 4\n");
   if (error = pthread_create(&t4,NULL,decthread,&num1))
      fprintf(stderr,"Error creating thread 4: %s\n",strerror(error));
   if (error = pthread_join(t1,NULL))
      fprintf(stderr,"Error joining thread 1: %s\n",strerror(error));
   if (error = pthread_join(t2,NULL))
      fprintf(stderr,"Error joining thread 2: %s\n",strerror(error));
   if (error = pthread_join(t3,NULL))
      fprintf(stderr,"Error joining thread 3: %s\n",strerror(error));
   if (error = pthread_join(t4,NULL))
      fprintf(stderr,"Error joining thread 4: %s\n",strerror(error));
   if (error = getcount(&count_now))
      fprintf(stderr,"Error getting count: %s\n",strerror(error));
   fprintf(stderr,"Count is %d\n",count_now);
   return 0;
}
   
