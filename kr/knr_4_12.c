#include <stdio.h>
#include <limits.h>
#include <string.h>

#define LEN 5

void itoa(int n, char s[]);//this function converts a decimal number into a string - in reverse mode
void reverse( char s[]);//this function reverses a string
int i;

int main(void)
{
   int ret = 0;
   int n[] =  {1, 12343, -123, 0, INT_MAX};
   int j = 0;

   printf("\nThis program uses recursion in order to transform an integer, into a string\n");
   while(j < LEN)
   {
      i = 0;
      char s[LEN + 1] = {0};
      itoa(n[j], s);
      s[i] = '\0'; 
     // printf("\n The value of the number %d is %s",n[j], s);
      i = 0;
      reverse(s);
      printf("\n The value of the number %d is %s",n[j], s);
      j++;
   }

   return ret;
}

void itoa(int n, char s[])
{

   if (n < 0)
   {
      itoa(-n,s);
      s[i++] = '-';
   }
   else if(n/10 > 0)
   {
      s[i++] = n%10 + '0';
      itoa(n/10, s);
   }
   else
      s[i++] = n%10 + '0';
}

void reverse(char s[])
{
   int c = 0;
  
   if (i < strlen(s)/2){ 
      c = s[i];
      s[i] = s[strlen(s) - i - 1];
      s[strlen(s) - i - 1] = c; 
      i++;
      reverse(s);
   }
}

