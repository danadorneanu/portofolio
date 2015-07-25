#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(keytab[0]))

/*
 * Struct containg 2 fields
 * -> word;
 * -> the word index.
 */

#define IN_QUOTES 5
#define OUT_QUOTES 6
#define IN_COMMENT_LINE 7
#define OUT_COMMENT_LINE 8
#define IN_COMMENT 9
#define OUT_COMMENT 10



struct key {
   char *word;
   int count;
} keytab[] = 
 {
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"continue", 0},
    {"do", 0},
    {"double", 0},
    {"float", 0},
    {"for", 0},
    {"go", 0},
    {"if", 0},
    {"int", 0},
    {"to", 0},
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0}
 };

#define BUFSIZE 100
char buf[BUFSIZE];/* the buffer used for get and ungetch */
int bufp = 0; /*next free position in buf */

/* delivers to next char to be 
 * read and gets it out from the buffer */
int getch(void);


/* pushes back one character into the 
 * shared buffer for it can be evaluated again */
void ungetch(int);


/* returns the fisrt character of the next word from the input and
 * assignes to word the entire next word */
int getword (char *, int);


/* Return a pointer to the funtion of binsearch;
 * binsearch -> aplies the algorithm binsearch to the predefined 
 * array keytab[] - in order to search for the the current word 
 * int the array key[0], key[1], ..., key[NKEYS - 1]. */
struct key *binsearch (char *, struct key *, int);

int main(void)
{
   int ret = 0;
   char word[MAXWORD + 1];
   struct key *k;
   
   printf("\nI count usual word from a C file\n Give me some input\n");
   while (getword(word, MAXWORD) != EOF)
      if (isalpha(word[0]))
         if ( (k = binsearch(word, keytab, NKEYS)) != NULL)
               k->count++;
   
   printf("\nHere is what I counted:\n");
   for (k = keytab; k < keytab + NKEYS; k++)
   //   if (k->count > 0)
         printf("%4d %s\n", k->count, k->word);

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

int getword(char *word, int lim)
{
   int c = 0;
   char *w = word;

   while (isspace(c = getch()))
      ;
   if (c != EOF)
      *w++ = c;

   if (!isalpha(c))
   {
      if (c == '"')
         while ( ((c = getch()) != '"') && (c != EOF))
               ;
      else if (c == '\\')
      {
         if ((c = getch()) == '\\')
         {
            while ( ((c = getch()) != '\n') && (c != EOF))
               ;
         }
         else if (c == '*')
         {
            while ((c = getch()) != EOF)
               if ( (c == '*') && ((c = getch()) == '\\'))
                  break;
               else
                  continue;
         }
      }
      else if ((c == '#') || ( c == '_'))
         *w++ = c;
      else
      {
         *w = '\0';
         return c;
      }
   }
   for (; --lim > 0; w++)
      if (!isalnum(*w = getch()))
      {
         if (c == '"')
         {
            
            while ( ((c = getch()) != '"') && (c != EOF))
               ;
            *w = '\0';
            break;
         }
         else if (c == '\\')
         {
            if ((c = getch()) == '\\')
            {
               while ( ((c = getch()) != '\n') && (c != EOF))
                  ;
               *w = '\0';
               break;
            }
            else if (c == '*')
            {
               while ((c = getch()) != EOF)
                  if ( (c == '*') && ((c = getch()) == '\\'))
                  {
                     *w = '\0';
                     break;
                  }
                  else
                  {
                     *w = '\0';
                     continue;
                  }
            }
         }
         else if ((c == '#') || ( c == '_'))
         {
            
            continue;
         }
         else
         {
            ungetch(*w);
               break;
         }
      }
         *w = '\0';

   return word[0];
}

struct key *binsearch(char *word, struct key *tab, int n)
{

   int cond = 0;
   struct key *low = &tab[0];
   struct key *high = &tab[n];
   struct key *mid;

   while (low < high)
   {
      mid = low + (high - low) / 2;
      if ( (cond = strcmp(mid->word , word)) < 0)
         low = mid + 1;
      else if (cond > 0)
         high = mid;
      else 
         return mid;
   }
   return NULL;
}
