#include <stdio.h>
#include <string.h>

#define MAX_LINELEN 1000
#define FALSE 0
#define TRUE 1


int strindex (char s[], char t[]);

int main (void)
{
   int ret = 0;
   int c = 0;
   int i = 0;
   char s[MAX_LINELEN + 1], t[MAX_LINELEN + 1];

   printf("\nGive me the string in which you want to search!\n\t");
   while ((i < MAX_LINELEN) && ((c = getchar()) != EOF) && (c != '\n'))
   {
      s[i ++] = c;
   }
   s[++i] = '\0';
   
   i = 0;
   printf("\nGive me the string that I should look for!\n\t");
   while ((i < MAX_LINELEN) && ((c = getchar()) != EOF) && (c != '\n'))
   {
      t[i ++] = c;
   }
   t[++i] = '\0';
   
   i = strindex(s, t);
   if (i > 0) 
      printf("The last apeareace of '%s' in '%s' is at location %d", t, s,i);
   else 
      printf("The string '%s' doesn't appear in '%s!", t, s);

   return ret;
}

int strindex (char s[], char t[])
{
   int i = 0, k = 0, j = 0; 

   for (i = strlen(s) - 1; i >= 0; i--)
   {
      for (j = i, k = strlen(t) - 1; ((s[j] == t[k]) && (k > 0)); j--, k--)
         ;
     if(k == 0)
        return i - strlen(t) + 1;
   }
   return -1;    
}
