#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "doneflag.h"
#include "globalerror.h"
#include "randsafe.h"
#include "sharedsum.h"
#define TEN_MILLION 10000000L

/* ARGSUSED */
void *computethread(void *arg1) {             /* compute a random partial sum */
   int error;
   int localdone = 0;
   struct timespec sleeptime;
   double val;

   sleeptime.tv_sec = 0;
   sleeptime.tv_nsec = TEN_MILLION;                                  /* 10 ms */

   while (!localdone) {
       if (error = randsafe(&val)) /* get a random number between 0.0 and 1.0 */
           break;
       if (error = add(sin(val)))
          break;
       if (error = getdone(&localdone))
          break;
       nanosleep(&sleeptime, NULL);                   /* let other threads in */
   }
   seterror(error);
   return NULL;
}
