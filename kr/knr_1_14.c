#include <stdio.h>
#define NR_DIFFCHAR 128
int main(void)
{
	int ret = 1;
   int c = 0;	
   int i = 0;
   int histogram[NR_DIFFCHAR];

   for (i = 0; i < NR_DIFFCHAR; i++)
      histogram[i] = 0;

	while ((c = getchar()) != EOF)
	{
      histogram[c]++;  
	}

   for (i = 1; i <= NR_DIFFCHAR; i++){
      if(histogram[i]){
         if(i == ' ')
         {
            printf("\n ' '.");
         }
         else 
            if (i == '\t') 
            {
               printf("\n \\t.");
            }
            else
               if (i == '\n'){
                  printf("\n \\n.");
               }
               else
                  printf("\n  %c.", i);
      }
      while (histogram[i])
      {
         printf("*");
         histogram[i]--;
      }
   }
	return ret;
}
