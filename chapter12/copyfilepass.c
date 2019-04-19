#include <unistd.h>
#include "restart.h"

void *copyfilepass(void *arg)  {
   int *argint;

   argint = (int *)arg;
   argint[2] = copyfile(argint[0], argint[1]);
   r_close(argint[0]);
   r_close(argint[1]);
   return argint + 2; 
}
