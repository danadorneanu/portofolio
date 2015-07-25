#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define LEN 13

void merge(int v[], int s,int m,int f);/* this function merges the already sorted elements
                                           v = my array;
                                           s = the start index;
                                           m = the middle index;
                                           f = the finish index;
                                           */
void merge_sort(int v[], int s, int f); /* this function uses recursiveness to 
                                           simplify the problem
                                           */

int main(void)
{
   int ret = 0;
   int i = 0, v[LEN] = {0};
   printf("\nThis program sorts %d elements random generated using merge sort\nThe elements are:\n\t", LEN);

   for (i = 0; i < LEN; i++)
   {
      v[i] = rand() % 10 + 1;
      printf(" %d",v[i]);
   }
   merge_sort(v, 0, LEN - 1);

   printf("\nThe sorted elements are:\n\t");
   for (i = 0; i < LEN; i++)
      printf(" %d",v[i]);
   printf("\n");

   return ret;
}

void merge(int v[], int s, int m, int f)
{
   int s1 = 0, s2 = 0;
   int left[LEN] = {0}, right[LEN] = {0};
   int i = 0, j = 0, k = 0;
   
   /* merging elements */
   s1 = m - s + 1;//the index in v where the left part finish
   s2 = f - m;//the index in v where the right part finish
  
   /* deviding the array */
   for (i = 0; i < s1; i++)
      left[i] = v[s + i];

   for (i = 0; i < s2; i++)
      right[i] = v[m + i + 1];
   
   left[s1] = right[s2] = INT_MAX;
   i = j = 0;

   /* putting the 2 subarrays already sorted 
    * in the right order into a bigger array
    * */
   for (k = s; k <= f; k++) 
      if(left[i] <= right[j])
         v[k] = left[i ++];
      else 
         v[k] = right[j ++];
  
   printf("\n\t[TEMP]The sorted elements are:\n\t\t");
   for (i = 0; i < LEN; i++)
      printf(" %d",v[i]);
   printf("\n");

}

void merge_sort(int v[], int s, int f)
{
   int m = 0;

   if(s < f)
   {
      m = ((s + f) / 2);
      merge_sort(v, s, m);
      merge_sort(v, m + 1, f);
      merge(v, s, m, f);
   }
}

