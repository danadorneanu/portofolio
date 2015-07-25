#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100
char buf[BUFSIZE];/* the buffer used for get and ungetch */
int bufp = 0; /*next free position in buf */
int getch(void);/* delivers to next char to be 
                   read and gets it out from the buffer
                   */
void ungetch(int);/* pushes back one character into the 
                     shared buffer for it can be evaluated again
                     */
int getint(int *pn);/*
                       gets next integer from an input. It returns
                       -> < 0 for EOF
                       -> > 0 for a number
                       -> = 0 for not a number                     
                     */

int main(void)
{
   int ret = 0;
   int a = 0;

   printf("This program gets next integer from input into *pn,\n So give me some input:");
   while(getint(&a) != EOF)
      if (getint(&a)>0)
         printf("\n\tYour value is %d", a);
      else
      {
         printf("\n\tThe value printed is not a number");
         continue;
      }

   return ret; 
}

int getch(void) /* get a (possibly pushed-back) character */
{
   return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)    /* push character back on input */
{
   if (bufp >= BUFSIZE)
      printf("ungetch: too many characters\n");
   else
      buf[bufp++] = c;
}

int getint(int *pn)
{
   int c = 0, sign = 1;

   while (isspace(c = getch()))   /* skip white space */
                      ;

   if ((!isdigit(c)) && (c != EOF) && (c != '+') && (c != '-'))
   {
      ungetch(c); /* it is not a number */
      return 0;
   }
   sign = (c == '-') ? -1 : 1;
   if ((c == '+') || (c == '-'))
      c = getch ();

   for (*pn = 0; isdigit(c); c = getch())
      *pn = 10 * (*pn) + (c - '0');
   *pn *= sign;
   if (c != EOF)
      ungetch(c);

   return c;
}
