#include <stdio.h>

#define IN 1
#define OUT 0

int main(void)
{
	int ret = 1;
   int c = 0;	
	int state = OUT;

	while ((c = getchar()) != EOF)
	{
		if (c == ' ' || c == '\n' || c == '\t')
		{
		   if(state == IN)
				putchar('\n');
			state = OUT;
		}
		else 
		{
			state = IN;						   	
			putchar(c);
		}
	}

	return ret;
}
