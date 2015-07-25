#include <stdio.h>
#include <ctype.h>

#define MAX_LENGTH 30

int htoi ();

int main (void)
{
   int ret = 0;
   int result = 0;
  /* 
   printf("isalnum(1) is %d", isalnum('1'));
   printf("isalnum(A) is %d", isalnum('A'));
   */
   result = htoi();
   if(result >= 0)
      printf("\nThe decimal form of the number is: %d\n", result);

   return ret;
}

int htoi ()
{
   int int_result = 0, cr_digit = 0;
   int i = 0;
   int c = 0;
   if (!( ((c = getchar()) == '0') && (((c = getchar()) == 'X') || (c == 'x'))))
   {
      printf("\n 1.U have a bad input! \n U should give a hexazecimal number (Example: 0x1A)!\n");
      int_result = -1;
   }
   else
   {
      while (((c = getchar()) != EOF) && (i < MAX_LENGTH))
      {
         i ++;
         if (i == MAX_LENGTH) 
         {
            printf("\n 2.Your input is too long for my intelect!");
            int_result = -1;
         }
         else if(!(isalpha(c) || isdigit(c)))
         {
            if(c != '\n')
            {
               //Why here? .. are u loco?
               printf("\n 5.U have a bad input! \n Hexazecimal numbers contain only digit and A,B,C,D,E,F (Example: 0x1A)!\n");
               //printf("\n isalpha( %3d ) is %d\n", c, isalpha(c));
               //printf("\n isdigit( %3d ) is %d\n", c, isdigit(c));
               int_result = -1;
            }
         }
         else
         {
            if (isupper(c))
            {
               if (c > 'F')
               {
                  printf("\n 3.U have a bad input! \n Hexazecimal numbers contain only digit and A,B,C,D,E,F (Example: 0x1A)!\n");
                  int_result = -1;
               }
               else 
                  cr_digit = c - 'A' + 10; 
            }
            else if (islower(c))
            {
               if (c > 'f')
               {
                  printf("\n 4.U have a bad input! \n Hexazecimal numbers contain only digit and a,b,c,d,e,f (Example: 0x1a)!\n");
                  int_result = -1;
               }
               else 
                  cr_digit = c - 'a' + 10;
            }        
            else 
               cr_digit = c - '0';
            int_result = 16 * int_result + cr_digit;
         }
      }
   }
   return int_result;
}

