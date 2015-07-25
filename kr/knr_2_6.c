#include <stdio.h>

/* Example 
 * x = 1111 0111 // = 247
 * y = 0101 0010 // = 82
 * result = 1110 1011 // = 235
 * n = 3; 
 * p = 4;
 */

unsigned getbits (unsigned x, int p, int n);
unsigned setbits (unsigned x, int p, int n, int y);

int main()
{
   int ret = 0; 
   int n = 3, p = 4;
   unsigned x = 247, y = 82; 

   printf("%u", setbits(x, p, n, y));
   
   return ret;
}

unsigned getbits (unsigned x, int p, int n)
{
   if ((p + 1 - n) < 0) 
      return ( x & (~( ~0 << n)));

   return ( (x >> (p + 1 - n)) & (~( ~0 << n)));
}

unsigned setbits (unsigned x, int p, int n, int y)
{
   unsigned x_prim = 0; /* x_prim = ( (x >> (p + 1 - n)) >> n) << n 
                           => x = 0011 1000 // 56 
                           => where the last 3 bits are the bits 2, 3, 4 from the original x, and the first 2 bits are 0; 
                        */
   unsigned y_prim = 0; /* y_prim = ceva ai
                           => y = 0000 0010 // 2
                           => where only the last 3 bits are y's original bits, the rest are 0 
                           */
   unsigned x_sec = 0; /* x_sec = ( x_prim | y_prim ) 
                      => x_sec = 0011 1010 
                      => where the last 3 bits are the last 3 bits from y
                      */
  unsigned x_final = 0; 
  
   x_prim = ( (x >> (p + 1 - n)) >> n) << n; 
   y_prim = getbits(y, 0, n); 
   x_sec = ( x_prim | y_prim );

   x_final = ((x_sec << (p + 1 - n)) | getbits (x, 0,(p + 1 - n)));

  return x_final; 
} 
