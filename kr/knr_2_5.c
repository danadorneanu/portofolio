#include <stdio.h>
#define MLENGTH 20

int any(char s1[MLENGTH], char s2[MLENGTH]);

int main()
{
   int ret = 0; 

   char s1[MLENGTH + 1], s2[MLENGTH + 1]; 
   int i = 0;
   int c = 0; 
   int result = 0;
   
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

   result = any(s1, s2);
   if (result > -1)
      printf("The first occurence of any charcater from s2 in s1 is at index %d \n", result);
   else 
      printf("There is no occurence of any character of s2 in s1 \n");

   return ret; 
}

int any(char s1[MLENGTH],char s2[MLENGTH])
{
   
   int i = 0, j = 0; 
   int contains = 0;

   for (i = 0; (s1[i] != '\0') && (contains == 0); i++)
      for (j = 0; (s2[j] != '\0') && (contains == 0); j++)
      {
         if (s1[i] == s2[j])
            contains = 1;
      }
   if (contains) 
      return i;
   
   return -1;
}

