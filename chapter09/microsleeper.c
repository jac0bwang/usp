#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
   int i;
   int microseconds;
   int count;
 
   if (argc != 3) {
      fprintf(stderr, "Usage:%s microseconds count\n", argv[0]);
      return 1;
   }
   microseconds = atoi(argv[1]);
   count = atoi(argv[2]);
   for ( ; ; ) {
      for (i=0; i<count; i++)
         usleep(microseconds);
      printf("\007");
      fflush(stdout);
   }
}
