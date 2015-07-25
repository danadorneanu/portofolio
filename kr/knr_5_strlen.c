#include <stdio.h>
//#include <ctype.h>

/*
 * strlen: return length of string s;
 */
int strlen (char *s);

int main(void)
{

   int ret = 0;
   char str[] = "bientot";
   printf("The lenght of the string %s id %d", str, strlen(str));


   return ret;
}

/*
int strlen (char *s)
{
   int n;

   for (n = 0; *s != '\0'; s++)
      n++;

   return n;
}
*/

int strlen(char *s)
{
   char *p = s;

   while(*p != '\0')
      p++;

   return s - p;
}
