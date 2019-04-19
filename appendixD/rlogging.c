#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#ifdef LUSETHREAD
#include <pthread.h>
#endif
#include "restart.h"
#include "rlogging.h"
#include "uici.h"

#define DEFAULT_HOST "localhost"
#define DEFAULT_PORT 20100

#define LOGGING_BUFSIZE PIPE_BUF
#define LOGGING_GENMAX 50

/* Note: LOGGING_BUFSIZE must be at most PIPE_BUF */

static int nextID = 0;
#ifdef LDEBUGGING
static int ldebug_flag = 1;
#else
static int ldebug_flag = 0;
#endif

#ifdef LUSETHREAD
static pthread_mutex_t ctime_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t generator_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t ID_mutex = PTHREAD_MUTEX_INITIALIZER;
#endif

/* Turn on debugging if debug = 1                                     */
void ldebug(int debug) {
   ldebug_flag = debug;
}

static long get_threadid() {
#ifdef NOTHREADID
   return 0L;
#else
#ifdef LUSETHREAD
   return (long)pthread_self();
#else
   return 1L;
#endif
#endif
}
 
/* Expand the generator, gen_fmt, into the buffer gen that has size gensize.
 * return 0 if fits, 1 if it does not.
 * %p is converted to process ID.
 * %t is converted to thread ID.
 * if (gen_fmt[0] == 0) then just then pid.tid is used.
 * at most one %p and one %t are allowed.
*/
static int expand_gen(const char *gen_fmt, char *gen, int gensize) {
   int needed;
   char *pp;
   char *pt;
   pp = strstr(gen_fmt, "%p");
   pt = strstr(gen_fmt, "%t");
   if (gen_fmt[0] == 0) {                           /* Use default generator */ 
#ifdef NOTHREADID
      needed = snprintf(gen, gensize, "%ld", (long)getpid());
#else
#ifdef LUSETHREAD
      needed = snprintf(gen, gensize, "%ld.%ld", (long)getpid(),
                        get_threadid());
#else
      needed = snprintf(gen, gensize, "%ld", (long)getpid());
#endif
#endif
   }
   else if ((pt == NULL) && (pp == NULL))
      needed = snprintf(gen, gensize, "%s", gen_fmt);
   else if (pt == NULL)
      needed = snprintf(gen, gensize, "%.*s%ld%s", (int)(pp-gen_fmt), gen_fmt,
                        (long)getpid(), pp+2);
   else if (pp == NULL) {
      needed = snprintf(gen, gensize, "%.*s%ld%s", (int)(pt-gen_fmt), gen_fmt,
                        get_threadid(), pt+2);
      }
   else if (pp < pt) {
      needed = snprintf(gen, gensize, "%.*s%ld%.*s%ld%s",
                       (int)(pp-gen_fmt), gen_fmt, (long)getpid(),
                       (int)(pt-pp-2), pp+2, get_threadid(), pt+2);
   }
   else {
      needed = snprintf(gen, gensize, "%.*s%ld%.*s%ld%s", (int)(pt-gen_fmt),
                     gen_fmt, get_threadid(), (int)(pp-pt-2), pt+2,
                     (long)getpid(), pp+2);
   }
   if (needed >= gensize)
      return 1;
   return 0;
}

#define RWBUFSIZE PIPE_BUF
/* Read from infd and write to outfd until an error or end-of-file occurs */
static void readwriteall(int infd, int outfd) {
   char buf[RWBUFSIZE];
   int bytes_read;

   while ((bytes_read = r_read(infd, buf, RWBUFSIZE)) > 0) {
      if (r_write(outfd, buf, bytes_read) != bytes_read) {
         if (ldebug_flag)
            fprintf(stderr, "Pipe write error\n");
         close(infd);
         close(outfd);
         return;
      }
   }
   if (bytes_read < 0) {
      if (ldebug_flag)
         fprintf(stderr, "Pipe read error\n");
   }
   close(infd);
   close(outfd);
}

/* Create a pipe and a child process.
 * All output is sent to the pipe.
 * The child process reads from the pipe and outputs to the network.
*/
static void go_through_pipe(LFILE *mf) {
   int childpid;
   int fds[2];

   if (pipe(fds) < 0) {
      if (ldebug_flag)
         fprintf(stderr, "Pipe creation failed\n");
      return;
   }
   childpid = fork();
   if (childpid < 0) {
      if (ldebug_flag)
         fprintf(stderr, "Fork failed\n");
      close(fds[0]);
      close(fds[1]);
      return;
   }
   if (childpid == 0) {                                        /* child code */
      close(fds[1]);
      readwriteall(fds[0], mf->fd);
      exit(0);
   }
   close(fds[0]);
   close(mf->fd);
   mf->fd = fds[1];
}

/* Set the parameters to the current time
 * return 0 on success and 1 on failure.
*/
static int set_times(unsigned long *secp, unsigned long *usecp) {
   struct timeval tp;

   if (gettimeofday(&tp, NULL))
      return 1;
   *secp = (unsigned long)tp.tv_sec;
   *usecp = (unsigned long)tp.tv_usec;
   return 0;
}
 
/* Create a string representing the time given by sec and usec in the
 *    buffer buf.  This assumes that buf is large enough.
 * Return 0 on success and 1 on failure.
*/
static int make_time_string(char *buf, unsigned long sec, unsigned long usec) {
   time_t clock;
   double fract;
   char *tm;
 
   clock = (time_t)sec;
   fract = usec/1000000.0;
   sprintf(buf+7, "%5.3f", fract);
#ifdef LUSETHREAD
   if (pthread_mutex_lock(&ctime_mutex))
      return 1;
#endif
   tm = ctime(&clock);
   strncpy(buf,tm+11,8);
#ifdef LUSETHREAD
   if (pthread_mutex_unlock(&ctime_mutex))
      return 1;
#endif
   return 0;
}
 
/* Log the string given by the last two parameters.
 * Use the given generator.
 * Return 0 on success and -1 on failure.
*/
static int lprintfgen(LFILE *mf, char *gen, char *fmt, va_list ap) {

   int blen;                                          /* size of data buffer */
   char buf[LOGGING_BUFSIZE];
   char buftemp[LOGGING_BUFSIZE];
   char genbuf[LOGGING_GENMAX];
   int ret;
   unsigned long sec;
   char timebuf[13];
   char *timep;
   char timesbuf[20];                      /* holds seconds and microseconds */
   unsigned long usec;
   int written;
   
   if (mf==NULL) {
      if (ldebug_flag)
         fprintf(stderr, "lprintf called with NULL first parameter\n");
      return -1;
   }
   if ( (mf->tmode) || (strstr(fmt, "%t") != NULL) )
      if (set_times(&sec, &usec) != 0) {
         if (ldebug_flag)
            fprintf(stderr, "Error getting current time\n");
         return -1;
      }
   if (mf->tmode)
      sprintf(timesbuf, "%lu;%lu;", sec, usec);
   else
      timesbuf[0] = 0;
   timep = strstr(fmt, "%t");
   if (timep != NULL) {
      if (make_time_string(timebuf, sec, usec) != 0) {
         if (ldebug_flag)
            fprintf(stderr, "Error making time string in lprintf\n");
         return -1;
      }
      if (strlen(fmt) + 13 >= LOGGING_BUFSIZE) {
            fprintf(stderr, "Format string is too long\n");
         return -1;
      }
      sprintf(buf, "%.*s%s%s", (int)(timep-fmt), fmt, timebuf, timep+2);
      ret = vsnprintf(buftemp, LOGGING_BUFSIZE, buf, ap);
   }
   else
      ret = vsnprintf(buftemp, LOGGING_BUFSIZE, fmt, ap);
   if ((ret < 0) || (ret >= LOGGING_BUFSIZE)) {
       if (ldebug_flag)
          fprintf(stderr, "Error in lprintf format string\n");
       return -1;
   }
   if (expand_gen(gen, genbuf, LOGGING_GENMAX) != 0) {
       if (ldebug_flag)
          fprintf(stderr, "Generator info does not fit\n");
   }
   blen = strlen(buftemp) + strlen(genbuf) + strlen(timesbuf);
   ret = snprintf(buf, LOGGING_BUFSIZE, "%d:%s%s;%s", blen+1,
                  timesbuf, genbuf, buftemp);
   if (ret >= LOGGING_BUFSIZE) {
       if (ldebug_flag)
          fprintf(stderr, "Error in lprintf: size too large to fit\n");
       return -1;
   }
   while (written = write(mf->fd, buf, ret), written == -1 && errno == EINTR) ;
   if (written != ret) {
      if (ldebug_flag)
         fprintf(stderr, "lprintf error writing to pipe\n");
      return -1;
   }
   return 0;
}

/* Open a connection to the given host and port for logging.
 * If host is NULL, use the environment variable LOGGINGHOST if it is set;
 *    otherwise, use the host "localhost".
 * If port is 0, use the environment variable LOGGINGPORT if it is set;
 *    otherwise, use the default port DEFAULT_PORT.
 * Return a pointer to an LFILE if successful, or NULL if unsuccessful.
*/
LFILE *lopen(char *host, int port) {
   int fd;
   LFILE *mf;
   char *portstr;

   if (host == NULL) {
      host = getenv("LOGGINGHOST");
      if (host == NULL)
         host = DEFAULT_HOST;
   }
   if (port <= 0) {
      portstr = getenv("LOGGINGPORT");
      if (portstr == NULL)
         port = DEFAULT_PORT;
      else
         port = atoi(portstr);
   }
   fd = u_connect(port, host);
   if (fd < 0) {
      if (ldebug_flag)
         fprintf(stderr, "Connection failed to host %s on port %d\n",
                 host,port);
      return NULL;
   }
   mf = (LFILE *)malloc(sizeof(LFILE));
   if (mf == NULL) {
      if (ldebug_flag)
         fprintf(stderr, "Memory allocation error for lopen\n");
      return NULL;
   }   
#ifdef LUSETHREAD
   if (pthread_mutex_lock(&ID_mutex))
      return NULL;
#endif
   mf->id = nextID++;
#ifdef LUSETHREAD
   if (pthread_mutex_unlock(&ID_mutex))
      return NULL;
#endif
   mf->fd = fd;
   mf->tmode = 0;
   mf->gen[0] = 0;
   go_through_pipe(mf);
#ifdef LSENDTIME
   lsendtime(mf);
#endif
   return mf;
}    

/* Close the connection corresponding to mf.
 * Return 0 on success and -1 on failure.
*/
int lclose(LFILE *mf) {

   if (mf == NULL) {
      if (ldebug_flag)
         fprintf(stderr, "lclose called with NULL parameter\n");
      return -1;
   }
   if (close(mf->fd) == -1) {
      if (ldebug_flag)
         fprintf(stderr, "lclose failed to close the connection\n");
   }
   free(mf);
   return 0;
}

/* Log the given string, using the default generator.
 * The parameters are similar to those of printf.
 * Return 0 on success and -1 on failure.
*/
int lprintf(LFILE *mf, char *fmt, ...) { 
   char genbuf[LFILE_GENLENGTH];
   va_list ap;   

   if (mf==NULL) {
      if (ldebug_flag)
         fprintf(stderr, "lprintf called with NULL first parameter\n");
      return -1;
   }
   va_start(ap, fmt);
#ifdef LUSETHREAD
   if (pthread_mutex_lock(&generator_mutex))
      return -1;
#endif
   strcpy(genbuf, mf->gen);
#ifdef LUSETHREAD
   if (pthread_mutex_unlock(&generator_mutex))
      return -1;
#endif
   return lprintfgen(mf, genbuf, fmt, ap);
} 

/* Log the given string, using the given generator.
 * The parameters are similar to those of printf.
 * Return 0 on success and -1 on failure.
*/
int lprintfg(LFILE *mf, char *gen, char *fmt, ...) {
   va_list ap;
   if (mf==NULL) {
      if (ldebug_flag)
         fprintf(stderr, "lprintf called with NULL first parameter\n");
      return -1;
   }
   va_start(ap, fmt);
   return lprintfgen(mf, gen, fmt, ap);
}

/* Set the default generator to the given one.
 * Return 0 on success and -1 on failure.
*/
int lgenerator(LFILE *mf, char *gen) {
   if (mf == NULL) 
      return -1;
   if (gen == NULL)
      mf->gen[0] = 0;
   if (strlen(gen) >= LFILE_GENLENGTH)
      return -1;
#ifdef LUSETHREAD
   if (pthread_mutex_lock(&generator_mutex))
      return -1;
#endif
   strcpy(mf->gen,gen);
#ifdef LUSETHREAD
   if (pthread_mutex_unlock(&generator_mutex))
      return -1;
#endif
   return 0;
}

/* Send the local time with each logged message.
 * Return 0 on success and -1 on failure.
*/
int lsendtime(LFILE *mf) {
   if (mf == NULL) 
      return -1;
   mf->tmode = 1;
   if (r_write(mf->fd, "-", 1) < 0) {
      if (ldebug_flag)
         fprintf(stderr, "Pipe write error\n");
      return -1;
   }
   return 0;
}
