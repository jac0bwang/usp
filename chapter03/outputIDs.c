#include <stdio.h>
#include <unistd.h>

int main(void) {
   printf("My real user ID is       %5ld\n", (long)getuid());
   printf("My effective user ID is  %5ld\n", (long)geteuid());
   printf("My real group ID is      %5ld\n", (long)getgid());
   printf("My effective group ID is %5ld\n", (long)getegid());
   return 0;
}
