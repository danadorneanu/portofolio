#include <stdio.h>
#include <stdlib.h>

#define LEN 40

void insertsort(int v[],int length);

int main(void)
{
   int ret = 0;
   int i = 0, v[LEN] = {0};
   printf("\nThis program sorts %d elements random generated using insert sort\nThe elements are:\n\t", LEN);

   for (i = 0; i< LEN; i++)
   {
      v[i] = rand() % 500 + 1;
      printf(" %d",v[i]);
   }

   insertsort(v, LEN);

   printf("\nThe sorted elements are:\n\t");
   for (i = 0; i< LEN; i++)
      printf(" %d",v[i]);
   printf("\n");

   return ret;
}

void insertsort(int v[], int length)
{
   int j = 0, key = 0, i = 0;

   for (j = 1; j < length; j++)
   {
      key = v[j];
      i = j - 1;
      while ((i >= 0) && v[i] > key) 
      {
         v[i + 1] = v[i];
         i--;
      }
      v[i + 1] = key;

   }
}
