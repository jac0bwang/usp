#include <stdio.h>
#include <unistd.h>

int main(void) {
   printf("This is my output.");
   fork();
   return 0;
}
