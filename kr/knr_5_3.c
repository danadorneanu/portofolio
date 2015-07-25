#include <stdio.h>

/* this function copies the string source to the end of dest */
void strcat1(char *dest, char *source);

int main(void)
{
   int ret = 0;
   char source[] = "Pouvez vous me dire quelle e la correct pronontiation?";
   char dest[] = "Q:";
   
   strcat1(dest, source);
   printf("\n%s\n", dest);

   return ret;
}
/*
void strcpy (char *dest, char *source)
{
   int i = 0;

   while ((dest[i] = source[i]) != '\0')
      i++;
}
*/
void strcat1 (char *dest, char *source)
{
   while (*dest++)
      ;
   dest--;
   while (*dest++ = *source++)
      ;
}
