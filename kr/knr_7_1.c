/*! \file knr_7_1.c
 * \brief This program converts the string read from stdin 
 * to lower or upper case depending from the format
 * you asked 
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*!
 * \fn void ST_tolower(char *s)
 * \brief Applies the function tolower to each character of the string s
 *    which is received as a parameter order to convert the entire
 *    string from lower and upper case to lower case.                    
 * \param char s - the string to be made tolower
 * \return void function 
 * */
void ST_tolower(char *s);

/*!
 * \fn void ST_toupper(char *s)
 * \brief Applies the function toupper to each character of the string s
 *    which is received as a parameter order to convert the entire
 *    string from upper and lower case to upper case.                    
 * \param char s - the string to be made toupper
 * \return void function 
 * */
void ST_toupper(char *s);

/*!
 * \fn int getline(char *str, int lim)
 * \brief reads an input line
 * \param str - the string in which puts the read line
 * \param lim - the maximum number of characters I can read
 * \return the len of the line I just read
 * */
int getline(char *str, int lim);

int main(int argc, char *argv[])
{
   int ret = 0; 
   char buffer[256] = {0}, *str = NULL;
   int len = 0;

   if (argc != 2)
   {
      printf("\nerorr: correct usage \"./bin_file -l/-u\" depending of the conversion you need -to_lower or -to_upper");
      return ret + 1;
   }

   printf ("Give me an input to convert:");
   ///
   /// reading the input - 255 caracters at once
   /// to concatenate it the str buffer
   ///
   while ( (len = getline(buffer, 255)) != 0)
   {
      str = (char*) realloc (str, 256 * sizeof(char));
      strcat(str, buffer);
      memset(buffer, 0, 256);
   }

   ///
   /// in case that there is any string to convert
   ///
   if ( str != NULL)
   {
   ///
   /// getting the user option : lower/upper case
   /// 
 
      if (!strcmp(argv[1], "-l"))
      {
         ST_tolower(str);
         printf("\nYou tolower string is:\n%s", str);
      }
      else if(!strcmp(argv[1], "-u"))
      {
         ST_toupper(str);
         printf("\nYou upper string is:\n%s", str);
      }
      else 
         printf("\nerorr: unknown command");
   }
   else 
      printf("\nerorr: Your string is null");

   return ret;
}

   
   
   
   
void ST_tolower(char *s)
{   
   while(*s)
   {
      *s = tolower(*s);
      s++;
   }
}

void ST_toupper(char *s)
{   
   while(*s)
   {
      *s = toupper(*s);
      s++;
   }
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


