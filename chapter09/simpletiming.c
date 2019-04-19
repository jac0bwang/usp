#include <stdio.h>
#include <time.h>
void function_to_time(void);

int main(void) {
   time_t tstart;  

   tstart = time(NULL);
   function_to_time();
   printf("function_to_time took %f seconds of elapsed time\n", 
           difftime(time(NULL), tstart)); 
   return 0;
}
