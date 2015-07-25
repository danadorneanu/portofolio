#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "calc.h"

#define MAXOP 100 /* The maximum number of chars */

int main(void)
{
   int type = 0;
   double op2 = 0.0, op1 = 0.0;
   char s[MAXOP + 1];
   char str[MAXOP + 1]; 
   printf ("\nGive me the Polish form of an expresion on a single line please: \n");

   while ((type = getop(s)) != EOF)
   {
      switch (type)
      {
         case NUMBER: 
            push (atof(s));
         break;
         case NEG_NUMBER:
            str[0] = '-';
            str[1] = '\0';
            push (atof(strcat(str,s)));
         break;
         case '+':
            push (pop() + pop());
         break;
         case '*':
            push (pop() * pop());
         break;
         case '/':
            op2 = pop();
            if (op2)
               push (pop() / op2);
            else
               printf("\n\t error: zero divisor\n");
         break;
         case '-':
            
            op2 = pop();
            push (pop() - op2);
         break;
         case '%':
            op2 = pop();
            op1 = pop();
            if ( (op1 - (int)op1) < ZERO_CONV 
                  && (op2 - (int)op2) < ZERO_CONV 
                  && (op1 > 0) && (op2 > 0))
               push ((int)op1 % (int)op2);
            else 
               printf("\n\terror: Operand modulo is allowed to work only with positive integers\n");
         break;
         case 's':
            push(sin(pop()));
         break;
         case 'e':
            push(exp(pop()));
         break;
         case 'p':
            op2 = pop();
            op1 = pop();
            push(pow(op1,op2));
         break;
         case '\n':
            printf("\n=\t%.6g\n", pop());
         break;
         default: 
            printf("\n\terror: unknown command %s\n", s);
         break;
      }
   }
   return 0;
}

