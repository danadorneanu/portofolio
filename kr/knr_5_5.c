#include <stdio.h>
#include <string.h>

#define YES 1
#define NO 0

///
/// This function copies the first num characters from source to dest
///
char *strncpy1(char *dest, char *source, int num);

///
/// This function  appends the first num characters of source to dest
///
char *strncat1(char *dest, char *source, int num);

///
/// This function  compares the first num characters of str1 to those of the string str2
///
int strncmp1(char *str1, char *str2, int num);


int main(void)
{
   int ret = 0;
   char dest[10000];
   int num = 0;

   char s[10000] = "Je veux lui dire,", t[] = "Je que je ne trouve pas le livre!";
   
   strncpy1(dest,s, 1000);
   printf("\nThe dest after strncpy is \n%s", dest);

   strncat1(s, t, 1000);
   printf("\nThe dest after strncat is \n%s", s);

   num = 3;
   if(strncmp1(s, t, num))
      printf("\n the first %d chars match", num);
   else
      printf("\n the first %d chars do not match", num);

   return ret; 
}

char *strncpy1(char *dest, char *source, int num)
{
   int i = 0;

   while( (i < num) && source)
      dest[i++] = *source++;
   dest[++i] = '\0';
   return dest;
}

char *strncat1(char *dest, char *source, int num)
{
   int i = 0;
   int a = strlen(dest);

   while( (i < num) && source)
      dest[a + (i++)] = *source++;
   dest[a + i] = '\0';
   return dest;
}


int strncmp1(char *str1, char *str2, int num)
{
   int i = 0;

   while( (i < num) && str1[i] && str2 && (str1[(i++)] == *str2++))
      ;
   if (i == num)
      return YES;
   else 
      return NO;
}
