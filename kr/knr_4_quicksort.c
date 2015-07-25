#include <stdio.h>

void quicksort (int a[], int p, int r);//the main routine for quicksort - combining the partial solutions 
int partition (int a[], int p, int r);//partitioning the array in two parts following the rule 
                                      //  ------------------------------------------
                                      //  |        el <= x     | x |     el > x     |
                                      //  -------------------------------------------
                                      //  where x is the pivot that we choose

void swap(int a[], int i, int j); //this functions swaps the elements with the index i,j  int the array a

/* 
 * Global variables used in the recursive functions 
 */

int main (void)
{
   int ret = 0;
   int i = 0;
   int a[] = {2, 8, 7, 1, 3, 5, 6, 4};

   printf("\nThis program sorts the following array using quicksort:\n\t");
   while(i < 8)
      printf("%d ", a[i++]);
   quicksort(a, 0, 8);

   printf("\nThe sorted array is:\n\t");
   i = 0;
   while(i < 8)
      printf("%d ", a[i++]);
   printf("\n");

   return ret;
}

void quicksort (int a[], int p, int r) 
{
   int q = 0;

   if (p < r)
   {
      q = partition (a, p, r);
      quicksort(a, p, q - 1);
      quicksort(a, q + 1, r);
   }
}

int partition (int a[], int p, int r)
{
   int i = 0, j = 0, x = 0;

   i = p;
   x = a[p];
   
   for (j = p + 1; j < r; j++)
      if (a[j] < x)
         swap(a, ++i, j);
   swap(a, i, p); // put the pivot in his place
   return i; //returning the pivot value
}

void swap (int a[],int i,int j)
{
   int aux = 0;

   aux = a[i];
   a[i] = a[j];
   a[j] = aux;
}

