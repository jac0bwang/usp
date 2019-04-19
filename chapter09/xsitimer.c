#include <stdio.h>
#include <sys/time.h>
#define MILLION 1000000L

void function_to_time(void);

int main(void) {
   long diftime;
   struct itimerval ovalue, value;

   ovalue.it_interval.tv_sec = 0;
   ovalue.it_interval.tv_usec = 0;
   ovalue.it_value.tv_sec = MILLION;                /* a large number */
   ovalue.it_value.tv_usec = 0;
   if (setitimer(ITIMER_VIRTUAL, &ovalue, NULL) == -1) {
      perror("Failed to set virtual timer");
      return 1;
   }
   function_to_time();                        /* timed code goes here */
   if (getitimer(ITIMER_VIRTUAL, &value) == -1) {
      perror("Failed to get virtual timer");
      return 1;
   }
   diftime = MILLION*(ovalue.it_value.tv_sec - value.it_value.tv_sec) +
               ovalue.it_value.tv_usec - value.it_value.tv_usec;
   printf("The function_to_time took %ld microseconds or %f seconds.\n",
            diftime, diftime/(double)MILLION);
   return 0;
}
