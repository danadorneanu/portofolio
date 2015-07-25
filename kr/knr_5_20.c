#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN   100
#define MAX_PARAM_NR 10

#define FALSE 0
#define TRUE 1

enum { NAME, PARENS, BRACKETS, PARAM };
void dcl(void);
void dirdcl(void);
int gettoken(void);
int tokentype;            /* type of last token */
char token[MAXTOKEN];     /* last token string */
char name[MAXTOKEN];      /* identifier name */
char datatype[MAXTOKEN];  /* data type = char, int, etc. */
char out[1000];
int param_no;
char *types[] = { "int", "char", "double", "float", "long", "short", "void"};
char params_types[MAX_PARAM_NR][MAXTOKEN];
char params[MAX_PARAM_NR][MAXTOKEN];
int tab_no;

#define BUFSIZE 100
/* the buffer used for get and ungetch */
char buf[BUFSIZE];
/*next free position in buf */
int bufp = 0; 
/* 
 * delivers to next char to be 
 * read and gets it out from the buffer
 * */
int getch(void);  
/* 
 * pushes back one character into the 
 * shared buffer for it can be evaluated again
 */
void ungetch(int);


void dcl(void);
void dirdcl(void);
int gettoken(void); /* return next token */

void print_sol();

int  main(void) /* convert declaration to words */
{
   int i = 0;
   int ret = 0;

   while (gettoken() != EOF) 
   {
//      if (tokentype != '\n')
  //       printf("syntax error\n");
      for (i = 0; i < tab_no; i++)
         printf("\t");
      if (name[0] && datatype[0])
         printf("%s: %s %s\n", name, out, datatype);

      strcpy(datatype, token); 
      out[0] = '\0';
      name[0] = '\0';
      dcl();        
      print_sol();
   }

   return ret;
}

void print_sol()
{
   int i = 0;

   for ( i = 0; i < tab_no; i++)
      printf("\t");
   printf("%s: %s %s\n", name, out, datatype);

   if (param_no)
   {
      tab_no++;
      for ( i = 0; i < tab_no - 1; i++)
         printf("\t");
      printf("with the following param:\n");
   }

   param_no = 0;
   out[0] = '\0';
   name[0] = '\0';
   datatype[0] = '\0';
   gettoken();
   strcpy(datatype, token);

   dcl();        
}

void dcl(void)
{
   int ns;
   for (ns = 0; gettoken() == '*'; ) /* count *'s */
      ns++;
   /* doing smthing fishy */
   if(tokentype == '(')
   {
      print_sol();
      dirdcl();
   }
   
   dirdcl();
   while (ns-- > 0)
      strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
   int type;
   if (tokentype == '\n')
      ;
   else if (tokentype == ',')
   {
      print_sol();
   }
   else if (tokentype == '(') 
   { 
      /* ( dcl ) */
      if(!param_no)
      {
         dcl();
         if (tokentype != ')')
            printf("error: missing )\n");
      }
   } 
   else if (tokentype == NAME) 
      /* variable name */
      strcpy(name, token);
   else if (tokentype == ')')
      ;
   else
   {
      printf("\n tmp: the tokentype is %d \n", tokentype);
      printf("error: expected name or (dcl)\n");
   }

   while ((type=gettoken()) == PARENS || type == BRACKETS)     
      if (type == PARENS || param_no)
         strcat(out, " function returning");
      else 
      {
         strcat(out, " array");
         strcat(out, token);
         strcat(out, " of");
      }
   if (param_no)
         strcat(out, " function returning");
}

int gettoken(void) /* return next token */
{
   int c = 0;
   char *p = token;
   while ((c = getch()) == ' ' || c == '\t')
      ;
   
   if (c == '\n')
      return tokentype = '\n';
   if (c == ',')
   {
      return tokentype = ',';
   }
   else if (c == '(') 
   {
      if ((c = getch()) == ')') 
      {

         strcpy(token, "()");
         return tokentype = PARENS;
      } 
      else 
      {
         ungetch(c); 
         while ((c = getch()) == ' ' || c == '\t')
            ;
         if ( isalpha(c))
            param_no++;
         ungetch(c);

         return tokentype = '(';
      }
   } 
   else if (c == ')')
      return tokentype = ')';
   else if (c == '[') 
   {
      for (*p++ = c; (*p++ = getch()) != ']'; )
         ;
      *p = '\0';
      return tokentype = BRACKETS;
   } 
   else if (isalpha(c)) 
   {
      for (*p++ = c; isalnum(c = getch()); )
         *p++ = c;
      *p = '\0';
      ungetch(c);

      return tokentype = NAME;
   } 
   else
      return tokentype = c;
}

int getch(void) /* get a (possibly pushed-back) character */
{
   return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)    /* push character back on input */
{
   if (bufp >= BUFSIZE)
      printf("ungetch: too many characters\n");
   else
      buf[bufp++] = c;
}


