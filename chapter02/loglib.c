#include <stdlib.h>
#include <string.h>
#include "log.h"
 
typedef struct list_struct {
     data_t item;
     struct list_struct *next;
} log_t;
 
static log_t *headptr = NULL;
static log_t *tailptr = NULL;
 
int addmsg(data_t data) {
   return 0;
}

void clearlog(void) {  
} 

char *getlog(void) {
   return NULL;
}
 
int savelog(char *filename) {
   return 0;
}
