#include <stdio.h>
#include <time.h> 
#define MILLION 1000000L
#define THOUSAND 1000

void function_to_time(void);
 
int main(void) {
   long diftime;
   struct itimerspec nvalue, ovalue;
   timer_t timeid;
 
   if (timer_create(CLOCK_REALTIME, NULL, &timeid) == -1) {
      perror("Failed to create a timer based on CLOCK_REALTIME");
      return 1;
   }
   ovalue.it_interval.tv_sec = 0;
   ovalue.it_interval.tv_nsec = 0;
   ovalue.it_value.tv_sec = MILLION;               /* a large number */
   ovalue.it_value.tv_nsec = 0;
   if (timer_settime(timeid, 0, &ovalue, NULL) == -1) {
      perror("Failed to set interval timer"); 
      return 1;
   }
   function_to_time();                       /* timed code goes here */
   if (timer_gettime(timeid, &nvalue) == -1) {
      perror("Failed to get interval timer value");
      return 1;
   }
   diftime = MILLION*(ovalue.it_value.tv_sec - nvalue.it_value.tv_sec) +
      (ovalue.it_value.tv_nsec - nvalue.it_value.tv_nsec)/THOUSAND;
   printf("The function_to_time took %ld microseconds or %f seconds.\n",
           diftime, diftime/(double)MILLION);
   return 0;
}
