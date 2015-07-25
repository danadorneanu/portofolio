#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100 /* The maximum number of chars */
#define NUMBER '0'
#define ZERO_CONV 0.00000001


/* define - uri pentru getch si ungetch */
#define MAX_BUFSIZE 100
char buf[MAX_BUFSIZE + 1]; /* buffer for ungetch */
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
   int c = 0;
   int i = 0;
   char s[MAXOP + 1];
 
   printf("\n Give me the string I need to test ungets: \n");

   while ((c = getchar()) != EOF)
      s[i ++] = c; 


   s[++i] = '\0';
   ungets(s);
   printf("\n\t Now the conten of buf is %s", buf);
   

   return 0;
}

void ungets (char c[])
{
   int i = 0;

   while ( (c[i] != '\0') && (ungetch(c[i])))
      i++;
   if (c[i] == '\0')
      printf("\n\tungets: to many characters\n");
}

int getch (void) /* get a (possibly pushed-back) char */
{
   return (bufp > 0) ? buf[--bufp] : getchar();
}

int ungetch (int c)
{
      
   if(bufp < MAX_BUFSIZE)
   {
      buf[bufp++] = c;
      return 1;
   }
   printf("\n\tungetch: to many characters\n");
   return 0;
}

