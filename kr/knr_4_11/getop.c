#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "calc.h"


int getop(char s[]) /* GETS operands and operators */
{
   int i = 0, c = 0, c_aux = 0;

   while ( ((s[0] = c = getch()) == ' ') || (c == '\t'))
      ;
   s[1] = '\0';
   i = 0;

   if (c == '-')
   {
      if ((c_aux = getch()) == ' ')
         return c;
      s[++i] = c_aux;
      return NEG_NUMBER;
   }

   if ((c == 's') || (c == 'p') || (c == 'e'))
   {
      getch();
      getch();
      return c;
   }
   
   if ((!isdigit(c)) && (c != '.') && (c != '-'))
      return c; /* not a number */
   if (isdigit(c))
      while (isdigit(s[++i] = c = getch()))
         ;
   if (c == '.')
      while (isdigit(s[++i] = c = getch()))
         ;
   
   s[i + 1] = '\0';
   if (c != EOF)
      ungetch(c);
   return NUMBER;
}

