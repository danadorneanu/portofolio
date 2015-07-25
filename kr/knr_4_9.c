#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100 /* The maximum number of chars */
#define NUMBER '0'
#define ZERO_CONV 0.00000001


/* define - uri pentru getch si ungetch */
#define MAX_BUFSIZE 100
int buf[MAX_BUFSIZE + 1]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */


/* standard input/output functions */
void ungets (char c[]);
int getch(void);
int ungetch(int); /* tare smekeră funcţia asta : 
                      face push la o valoare intr-un buffer 
                      pe care il imparte cu getch 
                   */
int main(void)
{
   int i = 0;
   char s[MAXOP + 1] = "ceva plus \0 ceva";

   ungets(s);

   printf("\n Your string containing EOF is");
   while(buf[i] > 0)
      printf("%c", buf[i++]);

   return 0;
}

void ungets (char s[])
{
   int i = 0;

   while ((ungetch(s[i])))
      i++;
}

int getch (void) /* get a (possibly pushed-back) char */
{
   return (bufp > 0) ? buf[--bufp] : getchar();
}

int ungetch (int c)
{
   if(bufp > MAX_BUFSIZE){
      printf("\n\tungetch: to many characters\n");
      return 0;
   }
       
   buf[bufp++] = c;
   return 1;
}

