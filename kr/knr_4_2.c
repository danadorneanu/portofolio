#include <stdio.h>
#include <ctype.h>
#include <math.h>
#define MAXLEN 100

double atof(char s[]);
int main(void)
{
   int ret = 0;
   char s[MAXLEN + 1];
   int c = 0, i = 0;

   printf("\nGive me a string to convert to float! Ex: -123.43, -234.34e-6;\n");
   while ((i < MAXLEN) && (c = getchar()) != EOF)
      s[i ++] = c;
   s[i + 1] = '\0';
   printf("\n=>\tThe string i'll convert is %s", s);
   printf("\n=>\tThe converted number is %lf", atof(s));

   return ret;
}

/* atof: convert string s to double */
double atof(char s[])
{
   double val = 0;
   double power = 0;
   int i = 0, sign_sig = 0, sign_exp = 0;

   for (i = 0; isspace(s[i]); i++)
      ;

   sign_sig = (s[i] == '-') ? -1 : 1;

   if (s[i] == '+' || s[i] == '-')
      i++;

   for (val = 0.0; isdigit(s[i]); i++)
      val = 10.0 * val + (s[i] - '0');

   if (s[i] == '.')
      i++;
   
   for (power = 1.0; isdigit(s[i]); i++)
   {
      val = 10.0 * val + (s[i] - '0');
      power /= 10;
   }
   if (s[i] == 'e' || s[i] == 'E')
      i++;
   sign_exp = (s[i] == '-') ? -1 : 1;

   if (s[i] == '+' || s[i] == '-')
      i++;
  // printf("\n Temp: My digit is %c", s[i]);
   /* I discovered that power goes crazy */
//   printf("\n 1.Temp: the exponen power is %lf", power);
   if (isdigit(s[i]))
      while (s[i] > '0')
      {
         if (sign_exp < 0)
            power /= 10;
         else 
            power *= 10;
         s[i]--;
      }
   /* I discovered that power goes crazy */
  // printf("\n 2.Temp: the exponen power is %lf", power);

   return sign_sig * val * power;
}
