#include <math.h>
#include <stdio.h>
#include <string.h>
#include "globalerror.h"
#include "sharedsum.h"

int showresults(void) {
   double average;
   double calculated;
   int count;
   double err;
   int error;
   int gerror;
   double perr;
   double sum;

   if (((error = getcountandsum(&count, &sum)) != 0) ||
       ((error = geterror(&gerror)) != 0)) {                  /* get results */
      fprintf(stderr, "Failed to get results: %s\n", strerror(error));
      return -1;
   }
   if (gerror) {          /* an error occurred in compute thread computation */
      fprintf(stderr, "Failed to compute sum: %s\n", strerror(gerror));
      return -1;
   }
   if (count == 0)
      printf("No values were summed.\n");
   else {
      calculated = 1.0 - cos(1.0);
      average = sum/count;
      err = average - calculated;
      perr = 100.0*err/calculated;
      printf("The sum is %f and the count is %d\n", sum, count);
      printf("The average is %f and error is %f or %f%%\n", average, err, perr);
   }
   return 0;
}
