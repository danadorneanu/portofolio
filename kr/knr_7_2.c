/*! \file knr_7_2.c
 * \brief Exercise 7-2. Write a program that will print arbitrary input in a sensible way. As a minimum,
 * it should print non-graphic characters in octal or hexadecimal according to local custom, and
 * break long text lines.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
///the number of times I use hex_dump
int nr = 0;
/*!
 * \fn char *hex_dump(char *input, int len)
 * \brief This function takes the len arbitrary bits from input and 
 * prints them to ouput in as following format:
 * 00000000h: FF AF FD 00 FF AF FD 00 FF AF FD 00 FF AF FD 00 ; ...saklj.d......
 * the first part coresponds the index of the couple given to the input
 * the second collon represents the hexadecimal value of the character
 * the third collon represent the character in a printable format. (The nonprintable characters are represented by .)
 *
 * \param char input - the input to manage
 * \param int len -> how many chars to manage
 * \return void function 
 * */
#define MAXLEN 48
char *hex_dump(char *input, int len)
{
   char *out_print = NULL;
   char *out_hex = NULL;
   char *out = NULL;
   char *p , *q;
   char hex[10];
   int i = 0;


   out_print = (char*) calloc(256, sizeof(char));
   out_hex = (char*) calloc(256, sizeof(char));
   out = (char*) calloc(256, sizeof(char));
   p = out_print;
   q = out_hex;

   while ( i < len)
   {
      if (isprint(input[i]))
      {
         *out_print = input[i];
         sprintf(out_hex, " %x", input[i]);
         out_print++, out_hex += 3;
      }
      else
      {
         *out_print = '.';
         sprintf(out_hex, " %2x", input[i]);
         out_print++, out_hex += 3;
      }
      i++;
   }
   *out_print = '\0';
   *out_hex = '\0';

   sprintf(hex, "%9x", 16 * nr);
   strcat(out, hex);
   strcat(out, "h:");
 
   strcat(out, q);
   strcat(out, " : ");
   strcat(out, p);
   strcat(out, "\n");
   nr ++;
   return out;
}

int main(int argc, char *argv[])
{
   int ret = 0;
   int i = 0;
   char *buffer;
   char output[ MAXLEN * MAXLEN] = {0};

   buffer = (char*) malloc (MAXLEN * sizeof(char));
   strcpy(buffer, "gkdf");

   while (i < MAXLEN)
   {
      strcat(output, hex_dump(buffer, 16));
      buffer += 16;
      i+=16;
   }
   
   printf("\nThe \"sensible\" output is:\n%s", output);

   return ret;
}

