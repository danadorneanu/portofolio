#include <stdio.h>

int main(void)
{
   int ret = 0;
   int c = 0, value = 0;

   while (c != EOF) 
   {
      value = ((c = getchar()) != EOF); 
      printf ("The result of value is:%d\n", value);
   }
	
   printf ("The EOF is %d\n", c);

   return ret;
	

}
