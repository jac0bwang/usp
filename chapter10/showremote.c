#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "hardwaretimer.h"
#include "rlogging.h"
#include "show.h"
#include "virtualtimers.h"
#define MILLION 1000000L
#define MSGBUFSIZE 256

static double initialtod = 0.0;
static LFILE *lf;
static int maxtimers;
static double gettime(void);
static double timetodouble(long interval);

static void snprintfappend(char *s, size_t n, const char *fmt, ...) { 
   va_list ap; 
   int sizeleft; 
 
   sizeleft = n - strlen(s) - 1; 
   if (sizeleft <= 0)
      return; 
   va_start(ap, fmt);
   vsnprintf(s + strlen(s), sizeleft, fmt, ap);
}
 
static void createlogstring(char *msg, int n) {       /* create string to log */
   int i;
 
   if (getrunning() >= 0)
      snprintfappend(msg, n, "\t%d\t", getrunning());
   else
      snprintfappend(msg, n, "\t\t");
   for (i = 0; i < maxtimers; i++)
      if (getvalue(i) >= 0)
         snprintfappend(msg, n, "(%d,%.3f) ",
                 i, timetodouble(getvalue(i)));
   snprintfappend(msg, n, "\t (%dE", getnumberevents());
   for (i = 0; i < getnumberevents(); i++)
      snprintfappend(msg, n, " %d", getevent(i));
   snprintfappend(msg, n, ")\n");
}

static double getrelativetime(void) {    /* seconds since showinit was called */
   return gettime() - initialtod;
}
 
static double gettime(void) {    /* seconds since January 1, 1970 as a double */
   double thistime = 0.0;
   struct timeval tval;
 
   if (gettimeofday(&tval, NULL))
      fprintf(stderr, "Warning, cannot get time of day\n");
   else
      thistime = tval.tv_sec + (double)tval.tv_usec/MILLION;
   return thistime;
}

static double timetodouble(long interval) {        /* microseconds to seconds */
   return (double)interval/MILLION;
}
 
/* ------------------------Public Functions --------------------------------- */
void showinit(int maxt) {      /* set initialtod to seconds since Jan 1, 1970 */
   initialtod = gettime();
   maxtimers = maxt;
   lf = lopen(NULL, 0);
   if (lf == NULL)
      fprintf(stderr,"Cannot open remote logger\n");
   else
      lsendtime(lf);
}

void show(int traceflag, const char *msg, long val1, long val2,
             int blockedflag) {         /* log timers with message for evtype */
   char genbuf[20];
   char msgbuf[MSGBUFSIZE];
   int wasblockedflag;
 
   if (!traceflag)
      return;
   wasblockedflag = blockinterrupt();
   if (val1 < 0)
      genbuf[0] = 0;
   else
      sprintf(genbuf, "Timer %ld", val1);
   snprintf(msgbuf, MSGBUFSIZE, "%8.4f: ", getrelativetime());
   snprintfappend(msgbuf, MSGBUFSIZE, "%s", msg);
   if (val1 >= 0)
      snprintfappend(msgbuf, MSGBUFSIZE, "\t%ld", val1);
   else
      snprintfappend(msgbuf, MSGBUFSIZE, "%s", "\t");
   if (val2 >= 0)
      snprintfappend(msgbuf, MSGBUFSIZE, "\t%ld", val2);
   else
      snprintfappend(msgbuf, MSGBUFSIZE, "%s", "\t");
   if (blockedflag)
      snprintfappend(msgbuf, MSGBUFSIZE, "%s", "\tB");
   else
      snprintfappend(msgbuf, MSGBUFSIZE, "%s", "\tU");
   if (blockedflag != wasblockedflag)
      snprintfappend(msgbuf, MSGBUFSIZE, "%s", "***");
   createlogstring(msgbuf, MSGBUFSIZE);
   lprintfg(lf, genbuf, msgbuf);
   if (!wasblockedflag)
      unblockinterrupt();
}
