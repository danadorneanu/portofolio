
/*This program sorts input lines */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000     /* max nr of lines to be sorted */
#define MAXLEN 1000       /* max length of any input line */
#define ALLOCSIZE 10000 /* size of available space */
#define N 3 

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free position */

char *lineptr[MAXLINES];  /* pointers to text lines */

/* readlines: read input lines and returns the number of lines */
int readlines(char *lineptr[], int nlines);

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines, int n);

/* getline: read a line into s, return length   */
int getline(char *, int);

/* return pointer to n characters */
char *alloc(int);

int main(int argc, char *argv[])
{
   int ret = 0;
   int nlines = 0;     /* number of input lines read */
   int n = N;

   printf("\n This program prints the last n lines from the input");
   printf("\n\t nis 10 by default but we can change it by running the program with %s -n new_n_value\n", argv[0]);
   if( (nlines = readlines(lineptr, MAXLINES)) > 0)
   {
      printf("\n");

      if (argc == 1)
      {
         ///printing the last 10 lines from the input
         writelines(lineptr, nlines, n);
      }
      else if (argc == 3)
      {
         /// printing the last n lines from the input
         writelines(lineptr, nlines, atoi(argv[2]));
      }
      else 
         printf("erorr for command line arguments");
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

void writelines(char *lineptr[], int nlines, int n)
{

   while( nlines-- > 0)
      if (nlines < n)
         printf("%s\n", *lineptr++);
      else lineptr++;
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

