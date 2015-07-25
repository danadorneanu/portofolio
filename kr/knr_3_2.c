#include <stdio.h>

#define MAXLEN 30

void escape(char s[], char t[]);

int main(void)
{
   int ret = 0;
   int c = 0, i = 0;
   char s[MAXLEN + 1], t[MAXLEN + 1];

   printf("\n Give the string that you have to copy that doesn't have more then %d chars, also \n", MAXLEN);
   while ((c = getchar()) != EOF)
   {
      if (i >= MAXLEN) 
      {
         printf("\n You give more data that I can process! \n");
         break;
      }

      t[i] = c;
      i++;
   }
   t[i + 1] = '\0';

   escape(s,t);
   printf("The string you typed is %s", s);

   return ret;
}

void escape(char *s, char *t)
{
   int i = 0;
   int j = 0; 


   while (t[i] != '\0')
   {
      switch(t[i])
      {
         case '\t': 
            s[j] = '\\';
            s[j + 1] = 't';
            j++;
         break;
         case '\n':
            s[j] = '\\'; // s[j++] = '\\';
            s[j + 1] = 'n';//s[j++] = '\n';
            j++;//gone
         break;
         default:
            s[j] = t[i];//s[j++] = t[i];
         break;
      }
      j++; //gone
      i++;
   }
   s[j++] = '\0';
}

