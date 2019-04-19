#include <pthread.h>
#include <sys/types.h>
#define MAX_PACK_SIZE 1024
#define MAX_TASKS 10
#define NUMTYPES 6

typedef enum ptype {NEWTASK, DATA, BROADCAST, DONE,
                    TERMINATE, BARRIER} packet_t;

typedef struct { 
     int compid;
     int taskid;
     packet_t type;
     int length;  
} taskpacket_t;

typedef struct { 
     int compid;                            /* computation ID for task */
     int taskid;                               /* task ID for the task */
     int writefd;                        /* holds dispatcher->child fd */
     int readfd;                         /* holds child->dispatcher fd */
     int recvbytes;
     int recvpacksets;
     int sentbytes;
     int sentpackets;
     pid_t taskpid;                   /* process ID of the forked task */
     pthread_t tasktid;             /* thread ID of task output thread */
     int barrier;         /* -1 if not at barrier, else barrier number */
     pthread_mutex_t mlock;                  /* mutex lock for element */
     int endinput;                   /* true if no more input for task */
} ntpvm_task_t;
