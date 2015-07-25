#include <stdio.h>
#include "calc.h"

/*something for push and pop */
#define MAXVAL 100 /* maximum free stack positio val */
int next_stak_p = 0;
double val[MAXVAL];

void push (double c);
double pop (void);

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


