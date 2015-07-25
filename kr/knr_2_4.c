#include <stdio.h>
#define MLENGTH 20

void squeeze(char s1[MLENGTH], char s2[MLENGTH]);

int main()
{
   int ret = 0; 

   char s1[MLENGTH + 1], s2[MLENGTH + 1]; 
   int i = 0;
   int c = 0; 
   
   s1[i] = '\0';
   s2[i] = '\0';

   printf("Give me the content of s1 please! \nThe maximum length is %d \n", MLENGTH);
   while ((i < MLENGTH) && ((c = getchar()) != EOF) && (c != '\n'))
   {
      s1[i++] = c;
   }
   s1[i++] = '\0';

   printf("Give me the content of s2 please! \nThe maximum length is %d \n", MLENGTH);
   i = 0; 
   while ((i < MLENGTH) && ((c = getchar()) != EOF) && (c != '\n'))
   {
      s2[i++] = c;
   }
   s2[i++] = '\0';

   squeeze (s1, s2);

   for (i = 0; s1[i] != '\0'; i++)
      printf("%c", s1[i]);

   return ret; 
}

void squeeze(char s1[MLENGTH],char s2[MLENGTH])
{
   
   int i = 0, j = 0, k = 0; 
   int ok = 0;
   int s2_length = 0;

   for (i = 0; s2[i] != '\0'; i++)
      ;
   s2_length = i; 

   for (i = 0, k = 0; s1[i] != '\0'; i++)
   {
      ok = 1;
      for (j = 0; s2[j] != '\0'; j++)
      {
         if (s1[i] == s2[j])
            ok = 0;
         else 
            if ( (j == s2_length - 1) && ok)
               s1[k++] = s1[i];
      }
   }
   s1[k] = '\0';

}

