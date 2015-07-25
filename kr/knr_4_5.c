#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXOP 100 /* The maximum number of chars */
#define NUMBER '0'
#define NEG_NUMBER 'n'
#define ZERO_CONV 0.00000001

/*something for push and pop */
#define MAXVAL 100 /* maximum free stack positio val */
int next_stak_p = 0;
double val[MAXVAL];

/* define - uri pentru getch si ungetch */
#define MAX_BUFSIZE 100
char buf[MAX_BUFSIZE + 1]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

/* stack functions */
int getop (char []);
void push (double c);
double pop (void);

/* standard input/output functions */
int getch(void);
void ungetch(int); /* tare smekeră funcţia asta : 
                      face push la o valoare intr-un buffer 
                      pe care il imparte cu getch */
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
/* STACK FUNCTIONS */
void push (double f)
{
   if (next_stak_p < MAXVAL)
      val[next_stak_p++] = f;
   else 
      printf("\n\terror: stack is full, can't push!");
}

double pop (void)
{
   if (next_stak_p > 0)
      return val[--next_stak_p];
   else
   {
      printf("\n\terror: stak is empty, can't pop!");
      return 0.0;
   }
}

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


int getch (void) /* get a (possibly pushed-back) char */
{
   return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch (int c)
{
   if(bufp >= MAX_BUFSIZE)
      printf("\n\tungetch: to many characters\n");
   else
      buf[bufp++] = c;
}

