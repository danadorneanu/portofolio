
/*This program sorts input lines */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000     /* max nr of lines to be sorted */
#define MAXLEN 1000       /* max length of any input line */
#define ALLOCSIZE 10000 /* size of available space */
static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free position */

char *lineptr[MAXLINES];  /* pointers to text lines */

/* readlines: read input lines */
int readlines(char *lineptr[], int nlines);

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines);

/* This function is in the man at the qsort description
 * It is very similar with strcmp - with the 
 * diference that it is more generic then it \
 * (it's param are pointers to void)
 */
static int cmpstringp(const void *p1, const void *p2);

/* This function is in the man at the qsort description
 * It is very similar with strcmp - with the 
 * diference that it is more generic then it \
 * (it's param are pointers to void)
 */
static int cmpstringp_inv(const void *p1, const void *p2);

/* getline: read a line into s, return length   */
int getline(char *, int);

/* return pointer to n characters */
char *alloc(int);

/* numcmp: compare s1 and s2 numerically */
static int numcmp(const void *s1, const void *s2);

/* numcmp: compare s1 and s2 numerically */
static int numcmp_inv(const void *s1, const void *s2);


int main(int argc, char *argv[])
{
   int ret = 0;
   int nlines = 0;     /* number of input lines read */

   printf("\ntesting atoi %d", atoi("123"));
   printf("\ntesting atoi %d", atoi("23"));

   printf("\nThis program alphabetically sorts the input lines\nGive me some input\n");



   if ((nlines = readlines(lineptr, MAXLINES)) >= 0) 
   {
      printf("\n\t The lines in unsorted order are:\n");
      writelines(lineptr, nlines);

      if (argc == 1)
      {
         qsort(lineptr, nlines, sizeof(char *), cmpstringp);
         printf("\n\t The lines sorted alphabetically in growing order are:\n");
         writelines(lineptr, nlines);
      }
      else if (argc == 2)
      {
         if(!strcmp(argv[1], "-r"))
         {
            qsort(lineptr, nlines, sizeof(char *), cmpstringp_inv);
            printf("\n\t The lines sorted alphabetically in reversed order are:\n");
            writelines(lineptr, nlines);
         }
         if(!strcmp(argv[1], "-n"))
         {
            qsort(lineptr, nlines, sizeof(char *), numcmp);
            printf("\n\t The lines sorted in num order are:\n");
            writelines(lineptr, nlines);
         }
      }
      else if (argc == 3)
      {
         if( (!strcmp(argv[1], "-r") && (!strcmp(argv[2], "-n"))) || 
             ((!strcmp(argv[1], "-n")) && (!strcmp(argv[2], "-r"))) )
         qsort(lineptr, nlines, sizeof(char *), numcmp_inv);
         printf("\n\t The lines sorted in reversed num order are:\n");
         writelines(lineptr, nlines);
      }
      else 
      {
         printf("\n error: wrong comand line parameters \n");
         return ret + 1; 
      }
      return ret;
   } 
   else 
   {
      printf("error: input too big to sort\n");
      return ret + 1;
   }
   return ret;
}


int readlines(char *lineptr[], int maxlines)
{
   int len = 0, nlines = 0;
   char *p, line[MAXLEN] = {};

   while ( (len = getline(line, MAXLEN)) > 0)
      if ((nlines >= maxlines) || ((p = alloc(len)) == NULL))
         return -1;
      else 
      {
         line[len - 1] = '\0'; /* delete newline */
         strcpy(p, line);
         lineptr[nlines++] = p;
      }
   return nlines;
}

void writelines(char *lineptr[], int nlines)
{
   while( nlines-- > 0)
      printf("%s\n", *lineptr++);
}

int getline(char *s, int lim)
{
   int c = 0, i = 0;

   for (i = 0; (i < lim-1) && ((c = getchar()) != EOF) && (c != '\n'); i++)
      *s++ = c;

   if (c == '\n')
   {
      i++;
      *s++ = c;
   }

   *++s = '\0';
   
   return i;
}


char *alloc(int n)   
{
   if (allocbuf + ALLOCSIZE - allocp >= n) 
   { /* it fits */
      allocp += n;
      return allocp - n; /* old p */
   } 
   else      /* not enough room */
      return 0;
}

static int cmpstringp(const void *p1, const void *p2)
{
   /* The actual arguments to this function are "pointers to
    * pointers to char", but strcmp() arguments are "pointers
    * to char", hence the following cast plus dereference 
    * */
    return strcmp(* (char * const *) p1, * (char * const *) p2);
}

/* numcmp: compare s1 and s2 numerically */
static int numcmp(const void *s1, const void *s2)
{
   if ( ((atoi(* (char * const *) s1)) - (atoi(* (char * const *) s2))) > 0)
      return 1;
   else if ( ((atoi( * (char * const *) s1)) - (atoi(* (char * const *) s2))) < 0)
      return -1;
   return 0;
}

static int cmpstringp_inv(const void *p1, const void *p2)
{
   /* The actual arguments to this function are "pointers to
    * pointers to char", but strcmp() arguments are "pointers
    * to char", hence the following cast plus dereference 
    * */
   int a = strcmp(* (char * const *) p1, * (char * const *) p2);
   a = -a;
   return a;
}
/* numcmp: compare s1 and s2 numerically */
static int numcmp_inv(const void *s1, const void *s2)
{
   if ( ((atoi(* (char * const *) s1)) - (atoi(* (char * const *) s2))) < 0)
      return 1;
   else if ( ((atoi( * (char * const *) s1)) - (atoi(* (char * const *) s2))) > 0)
      return -1;
   return 0;
}



