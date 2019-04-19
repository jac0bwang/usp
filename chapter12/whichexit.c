#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void *whichexit(void *arg) {
   int n;
   int np1[1];
   int *np2;
   char s1[10];
   char s2[] = "I am done";
   n = 3;
   np1[0] = n;
   np2 = (int *)malloc(sizeof(int));
   *np2 = n;
   strcpy(s1, "Done");
   return(NULL);
} 
