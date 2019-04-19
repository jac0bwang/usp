#include <pthread.h>
#include <stdio.h>
#include <string.h>

void *detachfun(void *arg);

int main() {

   int x;
   int ret;

   fprintf(stderr,"my threadid is %d\n",(int)pthread_self());
   x = 17;

   detachfun(&x);
   fprintf(stderr,"Returned from detachfun\n");

   return 0;
}
