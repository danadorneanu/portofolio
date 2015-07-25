#include <stdio.h>

int lower(int c);

int main()
{
   int ret = 0;
   int c = 0;
      
   printf("\n Give me some letters: \n");

   while ((c = getchar()) !=EOF)
   {
      putchar(lower(c));
   }
   

   return ret; 
}

int lower(int c)
{

   (c = (c >= 'A' && c <= 'Z')) 
      ? (c + 'a' - 'A' ) 
      : c;

   return c;
}
