#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
 
pthread_attr_t *makepriority(int priority) {    /* create attribute object */
   pthread_attr_t *attr;
   int error;
   struct sched_param param;
   
   if ((attr = (pthread_attr_t *)malloc(sizeof(pthread_attr_t))) == NULL)
      return NULL; 
   if (!(error = pthread_attr_init(attr)) && 
       !(error = pthread_attr_getschedparam(attr, &param))) {
       param.sched_priority = priority;   
       error = pthread_attr_setschedparam(attr, &param);
   }
   if (error) {                      /* if failure, be sure to free memory */
      free(attr); 
      errno = error;
      return NULL; 
   }
   return attr;
}
