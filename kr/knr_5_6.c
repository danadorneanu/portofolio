#include <stdio.h>
#include <string.h>

#define YES 1
#define NO 0

///
/// This take a string as parameter and returns in reverse order 
///
char *reverse(char *dest);

///
/// This function  finds the first occurence of s2 in s1 and returns the position from s1
///
int strindex(char *s1, char *s2);

///
/// This function  compares the first num characters of str1 to those of the string str2
///
int strncmp1(char *str1, char *str2, int num);


int main(void)
{
   int ret = 0;
   int num = 0;

   char s[10000] = "je", str[] = "ne" , t[] = "Je que je ne trouve pas le livre!";
   
   printf("\nThe reversed version is \n%s",reverse(s));
   
   
   printf("\n the first occurence of %s is %s:", str, t);
   num = strindex(t, str);
   if(num != -1)
      printf("%d", num);
   else
      printf("\n the %s doesn't exist in %s", str, t);
      

   return ret; 
}

char *reverse(char *str)
{
   int a = 0;
   int length = 0;
   char *str2 = str;
   str2 += (strlen(str) - 1);
   length = strlen(str);

   while ((str2 - str) > 0)
   {
      a = *str;
      *str = *str2;
      *str2 = a;
      
      str++;
      str2--;
   }
      
   return str - length/2;
}

int strindex(char *s1, char *s2)
{
   int length1 = strlen(s1), length2 = strlen(s2);
   char *s2_ = s2;
   char *s1_ = s1 + 1;


   for(s1_ = s1; *s1; s1++, s1_++) 
   {
      for(s2 = s2_; (*s1 == *s2) && *(s2); s2++, s1++)
         ;
      if(!(*s2))
         return length1 - strlen(s1) - length2;
      else 
         s1 = s1_;
   }

   return -1;
}

///* getop: get next character or numeric operand */
//int getop(char s[])
//{
//   int i, c;
//   while ((s[0] = c = getch()) == ' ' || c == '\t')
//      ;
//   s[1] = '\0';
//   if (!isdigit(c) && c != '.')
//      return c;      /* not a number */  
//   i = 0;
//   if (isdigit(c))    /* collect integer part */
//      while (isdigit(s[++i] = c = getch()))
//         ;
//   if (c == '.')      /* collect fraction part */
//      while (isdigit(s[++i] = c = getch()))
//         ;
//   s[i] = '\0';
//   if (c != EOF)
//      ungetch(c);
//   return NUMBER;
//}
//

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
