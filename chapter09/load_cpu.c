#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main  (int argc, char *argv[]) {
   int     i, n;

   if (argc != 2){   /* check for valid number of command line arguments */
      fprintf (stderr, "Usage: %s processes\n", argv[0]);
      return 1;
   }
   n = atoi(argv[1]);
   fprintf(stderr,"Using %d processes\n",n);
   for (i = 1; i < n; ++i)
       if (fork())
          break;
   for ( ; ; ) ;
}


