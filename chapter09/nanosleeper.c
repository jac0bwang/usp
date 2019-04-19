#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
   int i;
   int nanoseconds;
   int count;
   struct timespec slptm;
 
   if (argc != 3) {
      fprintf(stderr, "Usage:%s nanoseconds count\n", argv[0]);
      return 1;
   }
   nanoseconds = atoi(argv[1]);
   count = atoi(argv[2]);
   slptm.tv_sec = 0;
   slptm.tv_nsec = nanoseconds;
   for ( ; ; ) {
      for (i=0; i<count; i++)
         nanosleep(&slptm, NULL);
      printf("\007");
      fflush(stdout);
   }
}
