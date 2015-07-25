/*! \file knr_7_4.c
 * Exercise 7-4. Revise minprintf to handle more of the other facilities of printf.
 */
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLEN 40

/*!
 * \fn void minscanf(char *fmt, ...)
 * \brief minimal scanf with variable argument list 
 * \param char *fmt - the format argument
 * \param ... of the other arguments represent a pointer indicating where the corresponding converted input should be stored
 * \return - how many succesful asignments were made
 */
void minscanf(char *fmt, ...);

/*!
 * \fn void minprintf(char *fmt, ...)
 * \brief minimal printf with variable argument list 
 * \param char *fmt - each argument it's a string that will be evaluated with a certain rule defined in the first arg
 * \return - void function
 */
void minprintf(char *fmt, ...);

int main(void)
{
   int ret = 0;
   int d, i, o, h1, h2;
   unsigned int u1, u2;
   char c; 
   char s[MAXLEN];
   float f1, f2, f3;



   char print_str[] = "\ndecimal = %d\ndecimal = %i\noctal = %o\nhex = %x\nhex = %X\nunsigned = %u \nunsigned = %u \nchar = %c \nfloat = %f \nstring = %s \nfloat = %e \nfloat = %g \n";
   char scan_str[] = "%d %i %o %x %X %u %u %c %f %s %e %g";

   minprintf("\n This program uses minscanf to read input from stdin");
   minprintf("\n Give me the next types as input: %%d %%i %%o %%x %%X %%u %%u %%c %%f %%e %%g %%s\n");
   minscanf(scan_str, &d, &i, &o, &h1, &h2, &u1, &u2, &c, &f1, &f2 ,&f3, &s);

   minprintf("\n Your input is:");
   minprintf(print_str, d, i, o, h1, h2, u1, u2, c, f1, f2 ,f3, s);

   return ret;
}


void minscanf(char *fmt, ...)
{
   /// points to each unnamed arg in turn 
   va_list ap;   
   char *p, *sval;
   int *ival;
   unsigned int *uval;
   float *fval;
   char *ch;

   /// make ap point to 1st unnamed arg 
   va_start(ap, fmt); 

   /// defining the format
   for (p = fmt; *p; p++) 
   {
      /// if we find the special character defining the type de scanf
      if (*p == '%') 
         switch (tolower(*++p))
         {
            /// decimal number (int)
            case 'd':
            case 'i':
               ival = va_arg(ap, int *);
               scanf("%d", ival);
            break;

            /// unsigned octal number (with a leading zero) - int
            case 'o':
               ival = va_arg(ap, int *);
               scanf("%o", ival);
            break;

            ///  x, X - unsigned hexadecimal number (without a leading 0x or 0X), using abcdef or ABCDEF - int
            case 'x':
            case 'X':
               ival = va_arg(ap, int *);
               scanf("%x", ival);
            break;          

            /// unsigned octal number (with a leading zero) - int 
            case 'u':
               uval = va_arg(ap, unsigned int *);
               scanf("%u", uval);
            break;

            /// case single character - int
            case 'c':
               ch = va_arg(ap, char *);
               scanf("%c", ch);
            break;

            /// case float
            case 'f':
            ///  [-]m.dddddde+/-xx or [-]m.ddddddE+/-xx, where the number of d's is given by the precision (default 6).
            case 'e':
            /// use %e or %E if the exponent is less than -4 or greater than or equal to the precision; 
            /// otherwise use %f. Trailing zeros and a trailing decimal point are not printed.
            case 'g':
               fval = va_arg(ap, float *);
               scanf("%f", fval);
            break;

            /// case string
            case 's':
               sval = va_arg(ap, char *);
               scanf("%s", sval);
            break;
            
            /// no special charater is printed
            case '%':
               printf("%%");
            break;
            default:
               printf("\nerror: I don't know this format");
            break;

         }
      }
}

void minprintf(char *fmt, ...)
{
   va_list ap; /* points to each unnamed arg in turn */
   char *p, *sval;
   int ival;
   double dval;
   va_start(ap, fmt); /* make ap point to 1st unnamed arg */
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
