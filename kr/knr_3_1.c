#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>

#define N 400000000

int our_binsearch(int x, int v[], int n);
int knr_binsearch(int x, int v[], int n);

int main()
{
   int ret = 0;
   int x = 0;
   //int v[N];
   int *v = NULL;
   int location = 0;
   int i = 0; 
   //just to record the time usage
   struct tms time_b4_sort, time_aftr_sort;

   v = malloc (sizeof (int)*N);

   if (!v)
      return printf ("malloc issue\n");

   for (i  = 0; i < N; i++)
      v[i] = 2 * i + 1;

   times (&time_b4_sort);
   location = our_binsearch(x, v, N);
   times (&time_aftr_sort);
   printf ("The resources usage for our search on %d elements are:\nUser Time: %ld\nSystem Time: %ld\n",
            N, time_aftr_sort.tms_utime - time_b4_sort.tms_utime, time_aftr_sort.tms_stime - time_b4_sort.tms_stime);

   times (&time_b4_sort);
   location = knr_binsearch(x, v, N);
   times (&time_aftr_sort);

   printf ("The resources usage for KNR search on %d elements are:\nUser Time: %ld\nSystem Time: %ld\n",
            N, time_aftr_sort.tms_utime - time_b4_sort.tms_utime, time_aftr_sort.tms_stime - time_b4_sort.tms_stime);

   if(location > 0)
      printf ("\n\t The index of %d in v is %d\n", x, location); 
   else 
      printf ("\n\t The element doesn't exist in v\n");

   free (v);

   return ret;
}
int knr_binsearch (int x, int v[], int n)
{
   int low = 0, high = 0, mid = 0;

   low = 0;
   high = n - 1;
   while (low <= high)
   {
      mid = (low + high) / 2; 
      if (x < v[mid])
         high = mid - 1;
      else if (x > v[mid])
         low = mid + 1;
      else 
         return mid;
   }
   return -1;
}

int our_binsearch( int x, int v[], int n)
{
   int ret = -1;
   int low = 0, high = 0, mid = 0;

   low = 0;
   high = n - 1;

   while (low < high)
   {
       mid = (low + high) / 2;
       if (x > v[mid])
          low = mid + 1;
       else
          high = mid;
   }
       if(x == v[mid])
          ret = mid;

       return ret;
}

