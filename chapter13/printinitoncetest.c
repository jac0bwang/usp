#include <stdio.h>

int printinitonce(void);
extern int var;

int main(void) {
 
   printinitonce();
   printf("var is %d\n",var);
   printinitonce();
   printf("var is %d\n",var);
   printinitonce();
   printf("var is %d\n",var);
   return 0;
}
