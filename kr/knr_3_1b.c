#include <stdio.h>

int binsearch(int x, int v[], int n);

int main()
{
   int ret = 0;
   int x = 45;
   int v[] = { 1, 4, 6, 31, 43, 45, 56, 67, 76};
   int n = 9;
   int location = 0;

   printf("\n Finding the position of %d in the vertex: ", x);
   
   location = binsearch(x, v, n);
   if(location > 0)
      printf("\n\t The index of %d in v is %d\n", x, location + 1); 
   else 
      printf("The element doesn't exist in v\n");

   return ret;
}
int binsearch( int x, int v[], int n)
{
   int low = 0, high = 0, mid = 0;

   low = 0;
   high = n - 1;
   mid = (low + high) / 2; 

   while ((low <= high) && (v[mid]!=x))
   {
      if (x < v[mid])
         high = mid - 1;
      else 
         low = mid + 1;
      mid = (low + high) / 2; 
   }

   if(x == v[mid])
      return low;

   return -1;
}
