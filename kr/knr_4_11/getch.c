#include <stdio.h>

/* define - uri pentru getch si ungetch */
#define MAX_BUFSIZE 100
char buf[MAX_BUFSIZE + 1]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

/* standard input/output functions */
int getch(void);
void ungetch(int); /* tare smekeră funcţia asta : 
                      face push la o valoare intr-un buffer 
                      pe care il imparte cu getch */

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

