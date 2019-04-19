#include <stdio.h>

#define BUFSIZE 100

int passwordnosigs(char *prompt, char *passbuf, int passmax);

int main(void) {
   char *prompt = "Enter a password: ";
   char passbuf[BUFSIZE];
   int ret;

   ret = passwordnosigs(prompt,passbuf,BUFSIZE);
   if (ret == -1)
      perror("passwordnosigs error");
   else
      fprintf(stderr,"Got the password !%s!\n",passbuf);
   return 0;
}

   
