#include <stdio.h>

/* Example 
 * x = 1111 0101 // = 245
 */

int bitcount (char x);

int main()
{
   int ret = 0; 
   char x = -128;

   printf("The result is %d", bitcount(x));
   
   return ret;
}

int bitcount (char x)
{
   int idx = 0;

   for (idx = 0; x  != 0; idx ++)
      x &= (x - 1);

   return idx;
}
