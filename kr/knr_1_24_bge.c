#include <stdio.h>

int main(void)
{
   int ret = 0;
   int c = 0, col = 0, line = 0;
   int ocb = 0, osb = 0, op = 0;
   int sq = 0, dq = 0;
   int sc = 0, in_comm = 0;
   int in_parag_comm = 0, in_line_comm = 0;

   while ( ((c = getchar()) != EOF) && (ret == 0))
   {
      col ++;
      if (c == '\n')
      {
         line ++;
         col = 0;
         if (in_line_comm)
         {
            in_line_comm = 0;
            in_comm = 0;
         }
      }
      if (in_comm == 0)
      {
         if  (c == '{')
            ocb ++;
         else if (c == '}')
         {
            if (ocb == 0)
            {
               printf ("Line: %d, col: %d contains an open {\n", line, col);
               ret = -1;
            }
            else
               ocb --;
         }
         else if (c == '[')
            osb ++;
         else if (c == ']')
         {
            if (osb == 0)
            {
               printf ("Line: %d, col: %d contains an open [\n", line, col);
               ret = -1;
            }
            else
               osb --;
         }
         else if (c == '(')
            op ++;
         else if (c == ')')
         {
            if (op == 0)
            {
               printf ("Line: %d, col: %d contains an open )\n", line, col);
               ret = -1;
            }
            else
               op --;
         }
         else if (c == '\\')
         // We are escaping characters
         {
            c = getchar();
            
         }
         else if (c == '\"')
         {
            if (dq)
               dq --;
            else
               dq ++;
         }
      }
      if (c == '/')
      // This is a special character that might start a comment
      // Otherwise this should be inside of a single or double quote
      {
         if (sq)
         // We are in a single quote do nothing
            ;
         else if (dq)
         // We are in a double quote do nothing
            ;
         else if (in_comm)
         // We are in a comment do nothing
            ;
         else if (sc)
         // We have recieved a / before this one then this is a line comment
         {
            in_comm ++;
            in_line_comm ++;
         }
         else 
         // This should be the start of a comment
            sc ++;
      }
      else if (c == '*')
      {
         if (in_parag_comm)
         // We are in a paragraph comment be careful of next char
         {
            c = getchar ();
            if (c == '/')
            // The paragraph comment is over
            {
               in_comm = 0;
               in_parag_comm = 0;
            }
            else 
            // c is not / but could be a star
            {
               while (c == '*')
               // Read all * until they are depleted
                  c = getchar();
               if (c == '/')
               // We stopped on '/' then we are out of the comment
               {
                  in_comm = 0;
                  in_parag_comm = 0;
               }
            }
         }
         else if (sc)
         // We have recieved a / before this one then this is a paragraph comment
         {
            in_comm ++;
            in_parag_comm ++;
         }
         else
         // Anything else we do not care
            ;
      }
   }

   if (ocb && !ret)
      printf ("Open curly bracets mismatch\n");
   else if (osb && !ret)
      printf ("Open straight bracets mismatch\n");
   else if (op && !ret)
      printf ("Open parenthesis mismatch\n");
   else if (in_comm && !ret)
      printf ("Open comment\n");
      
   return ret;
}

