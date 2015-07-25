#include <stdio.h>

#define IN 1
#define OUT 0
#define MAX_WORDLENGTH 3

int main(void)
{
	int ret = 0;
   int c = 0;	
   int histogram[MAX_WORDLENGTH];
	int state = OUT;
   int length = 0;
   int i = 0;

   for (i = 0; i < MAX_WORDLENGTH; i++)
      histogram[i] = 0;

	while ((c = getchar()) != EOF)
	{
		if ( (c == ' ') || (c == '\n') || (c == '\t'))
      {
         if (state == IN)
         {
            histogram[length] ++;
            length = 0;
         }
			state = OUT;
      }
		else 
		{
		   state = IN;	
         length ++;
         if (length == MAX_WORDLENGTH)
            length --;
		}
	}

   for (i = 0; i < MAX_WORDLENGTH; i++)
   {
      printf("\n %d.", i);
      while (histogram[i])
      {
         printf("*");
         histogram[i]--;
      }
   }
   if (ret)
      printf ("Error in execution!!!!\n");

	return ret;
}

