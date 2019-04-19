#include <unistd.h>
#include <sys/time.h>

void function_to_time() {
   int i;
   for (i=0;i<100000000;i++) ;
}

/*
void function_to_time() {
   struct timeval tlast;
   gettimeofday(&tlast, NULL);
   gettimeofday(&tlast, NULL);
   gettimeofday(&tlast, NULL);
   gettimeofday(&tlast, NULL);
   gettimeofday(&tlast, NULL);
   gettimeofday(&tlast, NULL);
   gettimeofday(&tlast, NULL);
   gettimeofday(&tlast, NULL);
   gettimeofday(&tlast, NULL);
   gettimeofday(&tlast, NULL);
   gettimeofday(&tlast, NULL);
   gettimeofday(&tlast, NULL);
   gettimeofday(&tlast, NULL);
   gettimeofday(&tlast, NULL);
   gettimeofday(&tlast, NULL);
   gettimeofday(&tlast, NULL);
   gettimeofday(&tlast, NULL);
   gettimeofday(&tlast, NULL);
   gettimeofday(&tlast, NULL);
   gettimeofday(&tlast, NULL);
}
*/
