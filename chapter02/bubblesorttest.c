#include <stdio.h>

#define ARRAYSIZE 10

void bubblesort(int a[], int n);
int getcount();

int main(void) {
   int i;

   int a[ARRAYSIZE];
   printf("Enter %d integers to sort\n", ARRAYSIZE);
   for (i = 0; i < ARRAYSIZE; i++)
      scanf("%d", a+i);
   printf("Array follows:\n");
   for (i = 0;i < ARRAYSIZE; i++)
      printf("%2d: %4d\n", i, a[i]);
   bubblesort(a, ARRAYSIZE);
   printf("Sorted array follows:\n");
   for (i = 0; i < ARRAYSIZE; i++)
      printf("%2d: %4d\n", i, a[i]);
   printf("Number of ineterchanges: %d\n", getcount());
   return 0;
}


