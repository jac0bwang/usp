#include <errno.h>
#include <pthread.h>
static pthread_mutex_t listlock = PTHREAD_MUTEX_INITIALIZER;

int accessdata_r(void) {  /* return nonnegative traversal key if successful */ 
   int error;   
   int key;
   if (error = pthread_mutex_lock(&listlock)) {        /* no mutex, give up */
      errno = error;
      return -1; 
   }
   key = accessdata();
   if (key == -1) {
      error = errno;
      pthread_mutex_unlock(&listlock);
      errno = error;
      return -1;
   }
   if (error = pthread_mutex_unlock(&listlock)) {
      errno = error;
      return -1;
   }
   return key;
}

int adddata_r(data_t data) {        /* allocate a node on list to hold data */
   int error;
   if (error = pthread_mutex_lock(&listlock)) {        /* no mutex, give up */
      errno = error;
      return -1;
   }
   if (adddata(data) == -1) {
      error = errno;
      pthread_mutex_unlock(&listlock);
      errno = error;
      return -1;
   }
   if (error = pthread_mutex_unlock(&listlock)) {
      errno = error;
      return -1;
   }
   return 0; 
}

int getdata_r(int key, data_t *datap) {             /* retrieve node by key */
   int error;
   if (error = pthread_mutex_lock(&listlock)) {        /* no mutex, give up */
      errno = error;
      return -1;
   }
   if (getdata(key, datap) == -1) {
      error = errno;
      pthread_mutex_unlock(&listlock);
      errno = error;
      return -1;
   }
   if (error = pthread_mutex_unlock(&listlock)) {
      errno = error;
      return -1;
   }
   return 0; 
}

int freekey_r(int key) {                                    /* free the key */
   int error;
   if (error = pthread_mutex_lock(&listlock)) {        /* no mutex, give up */
      errno = error;
      return -1;
   }
   if (freekey(key) == -1) {
      error = errno;
      pthread_mutex_unlock(&listlock);
      errno = error;
      return -1;
   }
   if (error = pthread_mutex_unlock(&listlock)) {
      errno = error; 
      return -1;   
   } 
   return 0;  
}
