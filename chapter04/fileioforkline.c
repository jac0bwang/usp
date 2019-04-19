#include <stdio.h>
#include <unistd.h>

int main(void) {
   printf("This is my output.\n");
   fork();
   return 0;
}
