#include <stdio.h>

int my_func (void);

int main (void)
{
   int ret = 0;

   ret = my_func();

   return ret;
}

int my_func (void)
{
   int ret = 81;

   return ret;
   printf ("This is a test\n");
}

