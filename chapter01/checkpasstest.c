#include <stdio.h>

int checkpass(void);

int main(void) {
   int x;
   x = checkpass();
   fprintf(stderr, "x = %d\n", x);
   if (x)
      fprintf(stderr, "Password is correct!\n");
   else
      fprintf(stderr, "Password is not correct!\n");
   return 0;
}
