/*! \file knr_7_8.c
 * \brief cat:   concatenate files, version 2 
 */

#include <stdio.h>
#include <stdlib.h>

int main(int  argc, char *argv[])
{
   int ret = 0;
   FILE  *fp;
   void  filecopy(FILE *, FILE *);
   /// program name for errors 
   char  *prog = argv[0];

   /// no args; copy standard input 
   if (argc == 1 )       
      filecopy(stdin, stdout);
   else
      while (--argc > 0)
         if ((fp = fopen(*++argv, "r")) == NULL) 
         {
            fprintf(stderr, "%s: can't open %s\n", prog, *argv);
            exit(1);
         } 
         else 
         {
            filecopy(fp, stdout);
            fclose(fp);
         }

   if (ferror(stdout)) 
   {
      fprintf(stderr, "%s: error writing stdout\n", prog);
      exit(2);
   }

   return ret; 
}

/*! 
 * \fn void filecopy(FILE *ifp, FILE *ofp)
 * \brief filecopy: copy file ifp to file ofp 
 * \param: FILE *ifp - input file 
 * \param: FILE *ofp - output file
 * \return void
 */
void filecopy(FILE *ifp, FILE *ofp)
{
   int c;
   /// read one character at a time and writes it to the output file
   while ((c = getc(ifp)) != EOF)
      putc(c, ofp);
}

