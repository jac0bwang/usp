#include <errno.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include "msgqueuelog.h"
#define PERM (S_IRUSR | S_IWUSR)

typedef struct {
   long mtype;
   char mtext[1];
} mymsg_t;
static int queueid;

int initqueue(int key) {                    /* initialize the message queue */
   queueid = msgget(key, PERM | IPC_CREAT);
   if (queueid == -1) 
      return -1;
   return 0;
}

int msgprintf(char *fmt, ...) {               /* output a formatted message */
   va_list ap;
   char ch;
   int error = 0;
   int len;
   mymsg_t *mymsg;
 
   va_start(ap, fmt);                       /* set up the format for output */
   len = vsnprintf(&ch, 1, fmt, ap);              /* how long would it be ? */
   if ((mymsg = (mymsg_t *)malloc(sizeof(mymsg_t) + len)) == NULL)
      return -1;
   vsprintf(mymsg->mtext, fmt, ap);                 /* copy into the buffer */
   mymsg->mtype = 1;                            /* message type is always 1 */
   if (msgsnd(queueid, mymsg, len + 1, 0) == -1) 
      error = errno;
   free(mymsg);
   if (error) {
      errno = error;
      return -1;
   }
   return 0;
}

int msgread(void *buf, int len) {   /* read into buffer of specified length */
   return msgrcv(queueid, buf, len, 0, 0);
}

int msgwrite(void *buf, int len) {     /* output buffer of specified length */ 
   int error = 0;
   mymsg_t *mymsg;
   
   if ((mymsg = (mymsg_t *)malloc(sizeof(mymsg_t) + len - 1)) == NULL)
      return -1;
   memcpy(mymsg->mtext, buf, len);
   mymsg->mtype = 1;                            /* message type is always 1 */
   if (msgsnd(queueid, mymsg, len, 0) == -1)
      error = errno;
   free(mymsg);
   if (error) {
      errno = error;
      return -1;
   }
   return 0;
}

int remmsgqueue(void) { 
   return msgctl(queueid, IPC_RMID, NULL);
}
