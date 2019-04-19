#include <stdio.h>

int testandsetonce(int *oflag);

static void execute_once_test(int *var) {
   int error;
   int oflag;
 
   error = testandsetonce(&oflag);
   if (!error && !oflag) {
      *var = 1;
      printf("The variable has been initialized to 1\n");
   }
   else if (error)
      printf("Error initializing variable\n");
   else
      printf("variable already initilized, value is %d\n",*var);
}

int main(void) {
   int var;
 
   execute_once_test(&var);
   execute_once_test(&var);
   execute_once_test(&var);
   return 0;
}
