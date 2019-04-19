#include <stdio.h>

#define PASSMAX 10

int password(const char *prompt, char *passbuf, int passmax);

int main(void) {
   char *prompt = "enter your password: ";
   char passbuf[PASSMAX];
   int error;

   error = password(prompt, passbuf, PASSMAX);
   if (error)
      perror("password error");
   fprintf(stderr,"\nPassword is !%s!\n",passbuf);
   return 0;
}
