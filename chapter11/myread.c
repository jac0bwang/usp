#include <stdio.h>
#include <unistd.h>


int main() {
   char c;

   if (read(0,&c,1) != 1) {
      fprintf(stderr, "Cannot read first character\n");
      return 1;
   }
   if (write(1,&c,1) != 1) {
      fprintf(stderr, "Cannot write first character\n");
      return 1;
   }
   return 0;
}
