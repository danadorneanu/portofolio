#include <stdio.h>
#include <ctype.h>

#define MAX_LEN 50

void expand( char s1[MAX_LEN + 1], char s2[MAX_LEN + 1]);

int main(void)
{
   int ret = 0;
   char s1[MAX_LEN + 1], s2[MAX_LEN + 1]; 
   int c = 0, i = 0; 

   printf("\nTell me what string should I expand (Ex: a-z 
      \n\t=> I'll print all the letters from a to z)\n");
   while ((i < MAX_LEN) && ((c = getchar()) != EOF)) 
   {
      s1[i ++] = c;
   }
   s1[i + 1] = '\0';
   i = 0; 
   s2[i] = '\0';
   expand(s1, s2);
   printf("\n The list of chars you asked for is: %s\n", s2); 

   return ret;
}

void expand( char s1[MAX_LEN + 1], char s2[MAX_LEN + 1])
{
   int i = 0, j = 0; 

   for (i = 0; s1[i] != '\0'; i++)
   {
      if (s1[i] == '-')
      {
         if (j > 0)
            while (s2[j - 1] < s1[i + 1] - 1)
            {
               s2[j] = s2[j - 1] + 1; 
               j++;
            }
         else
            continue;
      }
      else if (isalnum(s1[i]))
      {
            s2[j] = s1[i];
            j++;
      }
         
   }
   s2[j + 1] = '\0';
}

