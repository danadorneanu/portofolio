#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define LEN 12
//#define MININT -2147483648;

//void itoa(int n, char s[]);
void itoa(char n, char s[]);
void reverse( char s[]);

int main(void)
{
   int ret = 0;
   //int n[] = {INT_MIN, -1, 0, -2147483647, 2147483647}, i = 0;
   char n[] = {-128, -1, 0, -127, 127}, i = 0;
   char s[LEN + 1];

   while (i < 5)
   {
      itoa(n[i], s);
      reverse(s);
      printf("\n The value of the number is %s\n", s);
      i++;
   }

   return ret;
}

//void itoa(int n, char s[])
void itoa(char n, char s[])
{
   int i = 0, sign = 0;
   unsigned char val = (unsigned) n;

   sign = n;
   i = 0;
   do
   {
      //s[i++] = abs(n - (n/10)*10) + '0';
      s[i++] = val - (val/10)*10 + '0';
   }
   while ((val /= 10));

   if (sign < 0)
      s[i++] = '-'; 
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


