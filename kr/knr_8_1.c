/* 
 * cat:   concatenate files, version 3 
 * Exercise 8-1. Rewrite the program cat from Chapter 7 using read, write, open, and close
 * instead of their standard library equivalents. Perform experiments to determine the relative
 * speeds of the two versions.
 */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define ERR -1
#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define BUFSIZE 256

int main(int  argc, char *argv[])
{
   int ret = 0;
   int fd = 0;
   void  filecopy(int , int);
   /// program name for errors 
   char *prog = argv[0];

   /// no args; copy standard input 
   if (argc == 1 )       
      filecopy(STDIN, STDOUT);
   else
      while (--argc > 0)
         if ((fd = open(*++argv, O_RDONLY, 0)) == ERR) 
         {
            fprintf(stderr, "%s: can't open %s\n", prog, *argv);
            exit(1);
         } 
         else 
         {
            filecopy(fd, STDOUT);
            close(fd);
         }

   if (ferror(stdout)) 
   {
      fprintf(stderr, "%s: error writing stdout\n", prog);
      exit(2);
   }

   return ret; 
}

/* 
 * @fn void filecopy(FILE *ifp, FILE *ofp)
 * @brief filecopy: copy file ifp to file ofp 
 * @param: FILE *ifp - input file 
 * @param: FILE *ofp - output file
 * @return void
 */

void filecopy(int fd_in, int fd_out)
{
   char buffer[BUFSIZE] = {0};
   
   ///read one character at a time and writes it to the output file
   while ((read(fd_in, buffer, BUFSIZE) ) > 0)
   {
      write(fd_out, buffer, strlen(buffer));
      memset(buffer, 0, BUFSIZE);
   }
}

