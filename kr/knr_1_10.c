#include <stdio.h>
#define EOF 'q'
int main(void)
{
   int ret = 0;
   int c = 0;

   printf("This program make tabs and backspaces visible in an unambiguos way.\nPress q to quit writing.\n"); 
	while ( (c = getchar ()) != EOF )  
   					
	{
		if(c == '\t') 
		{
			putchar ('\\');
			putchar ('t');
      }
	      	else
				{ 
					if(c == '\b') 
					{
			        putchar ('\\');
			        putchar ('b');
					}
		        else
		        {
						if(c == '\\') 
						{ 
				        putchar ('\\');
				        putchar ('\\');
          			}
						else 
						{
							putchar(c);
						}
					}	
				 }	
   }
	return ret;
}
