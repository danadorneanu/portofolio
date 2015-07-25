#include <stdio.h>

/* Example 
 * x = 1111 0101 // = 245
 * n = 3
 * result = 1011 1110 // = 190
 */

unsigned getbits (unsigned x, int p, int n);
unsigned rightrot (unsigned x, int n);

int main()
{
   int ret = 0; 
   int n = 3;
   unsigned x = 245;

   printf("The result is %u", rightrot(x, n));
   
   return ret;
}

unsigned getbits (unsigned x, int p, int n)
{
   if ((p + 1 - n) < 0) 
      return ( x & (~( ~0 << n)));

   return ( (x >> (p + 1 - n)) & (~( ~0 << n)));
}

unsigned rightrot (unsigned x, int n)
{
   unsigned x_prim = 0; 
   unsigned x_sec = 0; 
   unsigned x_final = 0; 
  
   int aux = 0, index = 0; 
   aux = 1;

   while (aux > 0)
   {
      aux *=2; 
      index ++;
   }
   index++;
   printf("\nthe unsigned is represented in %d bits\n", index);

   x_prim = getbits(x, 0, n);
   x_sec = x >> n;  
   x_prim = x_prim << (index - n);
   x_final = x_sec | x_prim;

  return x_final; 
} 
