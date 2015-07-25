#include <stdio.h>
#define TRUE 1
#define FALSE 0

int main(void)
{
   int ret = 0;
   int toput = 0;
   int c = 0;

   printf("This program replaces the strings that contain more than 1 blanks by a single blank\n");
   while ( (c = getchar ()) != EOF ) 
   {
      if(c == ' ') {
	if (toput == TRUE) 
	{
           putchar(c);
	   toput = FALSE;
	}
      }
      else
	{
	   putchar(c);
	   toput = TRUE;
	}

   }
   return ret;
}
