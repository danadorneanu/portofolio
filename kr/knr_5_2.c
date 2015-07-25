#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100
char buf[BUFSIZE];/// the buffer used for get and ungetch 
int bufp = 0; /// next free position in buf 

///
/// delivers to next char to be 
/// read and gets it out from the buffer
///
int getch(void);

/// 
/// pushes back one character into the 
/// shared buffer for it can be evaluated again
///
void ungetch(int);

///
/// gets next float from an input. It returns
/// -> < 0 for EOF
/// -> > 0 for a number
/// -> = 0 for not a number                     
///
float getfloat(float *pn);

int main(void)
{
   int ret = 0;
   float a = 0.0;

   printf("This program gets next float from input into *pn,\nSo give me some numbers:\n\t");

   while((a = getfloat(&a)) != -1)
         printf("\n\tYour value is %.2f\n", a);
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

float getfloat(float *pn)
{
   int c = 0, sign = 1, i = 0;

   

   while (isspace(c = getch()))   /* skip white space */
                      ;
   if (c == EOF) 
      return EOF;

   if ((!isdigit(c)) && (c != EOF) && (c != '+') && (c != '-') && (c != '.'))
   {
      ungetch(c); /* it is not a number */
      return 0.0;
   }
   sign = (c == '-') ? -1 : 1;
   if ((c == '+') || (c == '-'))
      c = getch ();

   for (*pn = 0; isdigit(c); c = getch())
      *pn = 10 * (*pn) + (c - '0');

   if (c == '.')
   {
      for (i = 0, c = getch(); isdigit(c); c = getch(), i++)
         *pn = (10 * (*pn) + (c - '0'));
      while(i)
      {
         *pn /= 10;
         i--;
      }   
   }

   *pn *= sign;
   if (c != EOF)
      ungetch(c);

   return *pn;
}
