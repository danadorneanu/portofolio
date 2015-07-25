//TO COVER ESCAPE_SEQUENCES

#include <stdio.h>

#define IN_S_QUOTES 0 // into Simple Quotes
#define OUT_S_QUOTES 1

#define IN_D_QUOTES 2 // into Double QUOTES
#define OUT_D_QUOTES 3

#define IN_L_COMMENTS 4 //into Line Comment
#define OUT_L_COMMENTS 5

#define IN_P_COMMENTS 6 //into Paragraph Comment
#define OUT_P_COMMENTS 7

#define IN_ESCAPE_SEQUENCE 8
#define OUT_ESCAPE_SEQUENCE 9

#define CLOSE 0
#define OPEN 1

int main(void)
{
   int ret = 0;
   int c_pprev = 0, c_prev = 0, c = 0;
   int square = CLOSE; //What were she drinking???
   int curly = CLOSE;
   int paranthesis = CLOSE;
   int quotes = CLOSE, quotes_type = 0;
   int comments = CLOSE, comments_type = CLOSE; 
   int row_nr = 0;
   

   while ( ((c = getchar()) != EOF) || (ret == 0))
   {
      // modification that occurs with the element that we treated when the \n happened
      if (c == '\n') 
      {
         row_nr++;
         if ( (comments == OPEN) && (comments_type == IN_L_COMMENTS))
         {
            comments_type = OUT_L_COMMENTS;
            comments = CLOSE;
         }
      }
      
      if (quotes == CLOSE)
      {
         if (comments == CLOSE)
         {
            if (c == '\"') 
            {
               quotes = OPEN;
               quotes_type = IN_D_QUOTES;
            }
            else if (c == '\'') // Do we need this else ??
            {
               quotes = OPEN;
               quotes_type = IN_S_QUOTES;
            }
            else if ((c == '/') && (c_prev == '/'))
            {
               comments = OPEN;
               comments_type = IN_L_COMMENTS;
            }
            else if ((c_prev == '/') && (c == '*'))
            {
               comments = OPEN;
               comments_type = IN_P_COMMENTS;
            } 
            else
            {
               if (c == '{')
                  curly++;
               else if (c == '}')
               {
                  if (curly)// Can we check only for non-zero values (curly)
                     curly--;
                  else
                     printf("\n %d: error: u put one wrong \'}\'\n", row_nr); // Can we break this?
               }
               else if (c == '(')
                  paranthesis++;
               else if (c == ')')
               {
                  if (paranthesis)
                     paranthesis--;
                  else
                     printf("\n %d: error: u put one wrong \')\'\n", row_nr);
               }
               else if (c == '[')
                  square++;
               else if (c == ']')
               {
                  if (square)
                     square--;
                  else
                     printf("\n %d: error: u put one wrong \']\'\n", row_nr);
               }
            }
         }         
         else if  ((comments == OPEN) && (comments_type == IN_P_COMMENTS))                         
         {
            if((c == '/') && (c_prev == '*') && (c_pprev != '/'))
            {//TO SOLVE /*/*/
                  comments = CLOSE;
                  comments_type = OUT_P_COMMENTS;
            }
         }
      }
      else if( quotes == OPEN) 
      {
         if ((c == '\"') && quotes_type = IN_D_QUOTES)
         {
            quotes = CLOSE;
            quotes_type = OUT_D_QUOTES
         }
         if ((c == '\'') && quotes_type = IN_S_QUOTES)
         {
            quotes = CLOSE;
            quotes_type = OUT_S_QUOTES
         }
         if ((c == '\n'))

      }
         //de tratat escape sequences
      c_pprev = c_prev;
      c_prev = c; 
   }
   if (paranthesis != CLOSE)
      printf("\nerror: u left unclosed %d \'(\'\n", paranthesis);

   if (square != CLOSE)
      printf("\nerror: u left unclosed %d \'[\'\n", square);

   if (curly != CLOSE)
	   printf("\n error: u left unclosed %d \'{\'\n", curly);
   if (comments != CLOSE)
      printf("\n error: u left unclosed comments\n"); 
/*/*/
   /* lkfd;s */

   return ret;
}

