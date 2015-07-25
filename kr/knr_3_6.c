#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define LEN 12
#define MININT -2147483648;

void itoa(int n, char s[], int width);
void reverse( char s[]);

int main(void)
{
   int ret = 0;
   int n =  -12;
   char s[LEN + 1];
   int width = 10;

   itoa(n, s, width);
   reverse(s);
   printf("\n The value of the number %d is\n%s", n, s);

   return ret;
}

void itoa (int n, char s[], int width)
{
   int i = 0, sign = 0;
   sign = n;
   i = 0;
   do
   {
      s[i++] = abs(n - (n/10)*10) + '0';
   }
   while ((n /= 10));

   if (sign < 0)
      s[i++] = '-'; 
   while (i < width)
      s[i++] = ' ';
   s[i] = '\0';
}

void reverse(char s[])
{
   int c = 0;
   int i = 0;
   
   for (i = 0; i < strlen(s) / 2; i++)
   {
      c = s[i];
      s[i] = s[strlen(s) - i - 1];
      s[strlen(s) - i - 1] = c; 
   }
}


