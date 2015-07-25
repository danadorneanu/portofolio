#include <stdio.h>
#define MAX_LENGTH 10000

void reverse (char something[MAX_LENGTH]);
int main (void)
{
   int ret = 0;
   char line[MAX_LENGTH];
   int c = 0, i = 0;
   
   while ((i < MAX_LENGTH) && ((c = getchar()) != EOF) && (c != '\n'))
   {
     line[i] = c;
     ++i;
   }
   line[i] = '\0';
   reverse (line);
   printf("%s", line);

   return ret;
}


void reverse (char something[MAX_LENGTH])
{
   char aux[MAX_LENGTH];
   int i = 0;
   int length = 0;
   for (i = 0; (something[i]);  ++i);
   length = i;
   for (i = 0; i < length; i++)
      aux[i] = something[length - i - 1];
   for (i = 0; i < length; i++)
      something[i] = aux[i];
}
