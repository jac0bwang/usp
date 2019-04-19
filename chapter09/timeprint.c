#include <stdio.h>
#include <time.h>

int main(void) {
   time_t tcurrent; 

   tcurrent = time(NULL);
   printf("The current time is %s", ctime(&tcurrent));
   return 0;
}
