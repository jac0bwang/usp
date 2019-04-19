#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <unistd.h>
#include "abstime.h"
#define INCTIME 0.01
#define NUMTIMES 1 
#define SPINTIME 0.0

int main(int argc, char *argv[]) {
   struct sigaction act;
   struct timespec clockres, currenttime;
   timer_data data;
   struct sigevent evp;
   sigset_t sigset;
   double tcalc, tend, tstart, ttotal;
 
   data.exitflag = 0;
   data.inctime = INCTIME;
   data.numtimes = NUMTIMES;
   data.spintime = SPINTIME;
   data.type = -1;
   if (argc > 1) {
       if (!strcmp(argv[1], "-r"))
          data.type = TYPE_RELATIVE;
       else if (!strcmp(argv[1], "-a"))
          data.type = TYPE_ABSOLUTE;
       else if (!strcmp(argv[1], "-p"))
          data.type = TYPE_PERIODIC;
   }
   if ( (argc < 2) || (argc > 5) || (data.type < 0) ){
      fprintf(stderr,
         "Usage:  %s -r | -a | -p [inctime [numtimes [spintime]]]\n",
         argv[0]);
      return 1;
   }
   if (argc > 2)
       data.inctime = atof(argv[2]);
   if (argc > 3)
       data.numtimes = atoi(argv[3]);
   if (argc > 4)
       data.spintime = atof(argv[4]);
   fprintf(stderr, "pid = %ld\n", (long)getpid());
 
   act.sa_flags = SA_SIGINFO;
   act.sa_sigaction = timehandler;
   if ((sigemptyset(&act.sa_mask) == -1) || 
       (sigaction(SIGALRM, &act, NULL)) == -1) {
      perror("Failed to set handler for SIGALRM");
      return 1;
   }
   evp.sigev_notify = SIGEV_SIGNAL;
   evp.sigev_signo = SIGALRM;
   evp.sigev_value.sival_ptr = &data;
   if (timer_create(CLOCK_REALTIME, &evp, &data.timid) < 0) {
      perror("Failed to create a timer");
      return 1;
   }
   if (clock_getres(CLOCK_REALTIME, &clockres) == -1)
      perror("Failed to get clock resolution");
   else
      fprintf(stderr, "Clock resolution is %0.3f microseconds or %0.6f sec.\n",
         D_MILLION*time_to_double(clockres), time_to_double(clockres));
   data.tvalue.it_interval.tv_sec = 0;
   data.tvalue.it_interval.tv_nsec = 0;
   data.tvalue.it_value = double_to_time(data.inctime);
   data.flags = 0;
   if (clock_gettime(CLOCK_REALTIME, &currenttime) == -1) {
      perror("Failed to get current time");
      return 1;
   }
   tstart = time_to_double(currenttime);
   if (data.type == TYPE_ABSOLUTE) {
      data.tvalue.it_value.tv_nsec += currenttime.tv_nsec;
      data.tvalue.it_value.tv_sec += currenttime.tv_sec;
      if (data.tvalue.it_value.tv_nsec >= BILLION) {
         data.tvalue.it_value.tv_nsec -=  BILLION;
         data.tvalue.it_value.tv_sec++;
      }
      data.flags = TIMER_ABSTIME;
      fprintf(stderr,"Using absolute time\n");
   }
   else if (data.type == TYPE_RELATIVE) 
      fprintf(stderr,"Using relative time\n");
   else if (data.type == TYPE_PERIODIC) {
      data.tvalue.it_interval = data.tvalue.it_value;
      fprintf(stderr,"Using periodic time\n");
   }
   fprintf(stderr, "Interrupts: %d at %.6f seconds, spinning %.6f\n",
         data.numtimes, data.inctime, data.spintime);
   if (timer_settime(data.timid, data.flags, &data.tvalue, NULL) == -1){
      perror("Failed to start timer");
      return 1;
   }
   if (sigemptyset(&sigset) == -1) {
      perror("Failed to set up suspend mask");
      return 1;
   }
   while (!data.exitflag)
      sigsuspend(&sigset);
   if (clock_gettime(CLOCK_REALTIME, &currenttime) == -1) {
      perror("Failed to get expiration time");
      return 1;
   }
   tend = time_to_double(currenttime);
   ttotal=tend - tstart;
   tcalc = data.numtimes*data.inctime;
   fprintf(stderr, "Total time: %1.7f, calculated: %1.7f, error = %1.7f\n",
       ttotal, tcalc, ttotal - tcalc);
   return 0;
}     
