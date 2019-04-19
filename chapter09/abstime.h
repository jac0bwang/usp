#define BILLION  1000000000L
#define D_BILLION 1000000000.0
#define D_MILLION 1000000.0
#define TYPE_ABSOLUTE 0
#define TYPE_RELATIVE 1
#define TYPE_PERIODIC 2

typedef struct {
   timer_t timid;
   int type;
   int flags;
   int numtimes;
   int exitflag;
   double inctime;
   double spintime;
   struct itimerspec tvalue;
} timer_data;

struct timespec double_to_time(double tm);
double time_to_double(struct timespec t);
void timehandler(int signo, siginfo_t* info, void *context);
