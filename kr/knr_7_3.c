/*! \file knr_7_3.c
 * Exercise 7-3. Revise minprintf to handle more of the other facilities of printf.
 */
#include <stdarg.h>
#include <stdio.h>

/*
 * \fn void minprintf(char *fmt, ...)
 * \brief minimal printf with variable argument list 
 * \param char *fmt - each argument it's a string that will be evaluated with a certain rule defined in the first arg
 * \return - void function
 */
void minprintf(char *fmt, ...);

int main(void)
{
   int ret = 0;


   char str[] = "decimal = %d\ndecimal = %i\noctal = %o\nhex = %x\nhex = %X\nunsigned = %u \nunsigned = %u \nchar = %c \nfloat = %f \nstring = %s \ndouble = %e \ndouble = %E \ndouble = %g \n%%%% = %% \n";


   minprintf(str, 10, 34, 8, 16, 255, -1, 1, 'a', 12.54, "hello world", 32.54, 0.21, 0.00000000054);

   return ret;
}


/*!
 * minprintf: minimal printf with variable argument list 
 * */
void minprintf(char *fmt, ...)
{
   /// 
   /// points to each unnamed arg in turn
   ///
   va_list ap;   
   char *p, *sval;
   int ival;
   double dval;

   /// 
   /// make ap point to 1st unnamed arg */
   ///
   va_start(ap, fmt); 
   for (p = fmt; *p; p++) 
   {
      if (*p != '%') 
      {
         putchar(*p);
         continue;
      }
      switch (*++p) 
      {
         /// decimal number (int)
         case 'd':
         case 'i':
            ival = va_arg(ap, int);
            printf("%d", ival);
         break;

         /// unsigned octal number (with a leading zero) - int
         case 'o':
            ival = va_arg(ap, int);
            printf("%o", ival);
         break;

         ///  x, X - unsigned hexadecimal number (without a leading 0x or 0X), using abcdef or ABCDEF - int
         case 'x':
         case 'X':
            ival = va_arg(ap, int);
            printf("%x", ival);
         break;          

         /// unsigned octal number (with a leading zero) - int 
         case 'u':
            ival = va_arg(ap, unsigned int);
            printf("%u", ival);
         break;

         /// case single character - int
         case 'c':
            ival = va_arg(ap, int);
            printf("%c", ival);
         break;

         /// case float
         case 'f':
            dval = va_arg(ap, double);
            printf("%f", dval);
         break;

         /// case string
         case 's':
            for (sval = va_arg(ap, char *); *sval; sval++)
               putchar(*sval);
         break;
 
         ///  [-]m.dddddde+/-xx or [-]m.ddddddE+/-xx, where the number of d's is given by the precision (default 6).
         case 'e':
         case 'E':
            dval = va_arg(ap, double);
            printf("%e", dval);
         break;

         /// use %e or %E if the exponent is less than -4 or greater than or equal to the precision; 
         /// otherwise use %f. Trailing zeros and a trailing decimal point are not printed.
         case 'g':
         case 'G':
            dval = va_arg(ap, double);
            printf("%g", dval);
         break;

         /// no special charater is printed
         case '%':
            printf("%%");
         break;
         default:
            putchar(*p);
         break;
      }
   }
}
