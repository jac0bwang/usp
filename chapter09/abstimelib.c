#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <unistd.h>
#include "abstime.h" 

static struct timespec add_to_time(struct timespec t, double tm) {
   struct timespec t1;

   t1 = double_to_time(tm);
   t1.tv_sec = t1.tv_sec + t.tv_sec;
   t1.tv_nsec = t1.tv_nsec + t.tv_nsec;
   while (t1.tv_nsec >= BILLION) {
      t1.tv_nsec = t1.tv_nsec - BILLION;
      t1.tv_sec++;
   }
   return t1;
}

static int spinit (double stime) {    /* loops for stime seconds and returns */
   struct timespec tcurrent;
   double tend, tnow; 
 
   if (stime == 0.0)
      return 0;
   if (clock_gettime(CLOCK_REALTIME, &tcurrent) == -1)
      return -1;
   tnow = time_to_double(tcurrent);
   tend = tnow + stime;
   while (tnow < tend) {
      if (clock_gettime(CLOCK_REALTIME, &tcurrent)  == -1)
         return -1;
      tnow = time_to_double(tcurrent);
   }
   return 0;
}

/* ------------------------- Public functions -------------------------- */ 

double time_to_double(struct timespec t) {
   return t.tv_sec + t.tv_nsec/D_BILLION;
}
 
struct timespec double_to_time(double tm) {
   struct timespec t;
 
   t.tv_sec = (long)tm;
   t.tv_nsec = (tm - t.tv_sec)*BILLION;
   if (t.tv_nsec == BILLION) {
      t.tv_sec++;
      t.tv_nsec = 0;
   }
   return t;
}
 
void timehandler(int signo, siginfo_t* info, void *context) {
   timer_data *datap;
   static int timesentered = 0;
 
   timesentered++;
   datap = (timer_data *)(info->si_value.sival_ptr);
   if (timesentered >=  datap->numtimes) {
      datap->exitflag = 1;
      return;
   }
   if (spinit(datap->spintime) == -1) {
      write(STDERR_FILENO, "Spin failed in handler\n", 23);
      datap->exitflag = 1;
   }
   if (datap->type == TYPE_PERIODIC)
      return;
   if (datap->type == TYPE_ABSOLUTE)
      datap->tvalue.it_value =
         add_to_time(datap->tvalue.it_value, datap->inctime);
   if (timer_settime(datap->timid, datap->flags, &datap->tvalue, NULL) == -1) {
      write(STDERR_FILENO, "Could not start timer in handler\n",33);
      datap->exitflag = 1;
   }
}
