#include <stdio.h>

int printinitmutex(int *var, int value);

static void print_once_test(int *var) {
   int error;
 
   error = printinitmutex(var,1);
   if (error)
      printf("Error initializing variable\n");
   else
      printf("OK\n");
}

int main(void) {
   int var;
 
   print_once_test(&var);
   print_once_test(&var);
   print_once_test(&var);
   return 0;
}
