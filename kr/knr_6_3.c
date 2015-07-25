/**
 * @file knr_6_3.c 
 * @author Daniela Dorneanu 
 * @date   8 - 09 - 2008
 * @brief cross-referencer to print a list of all different words in a document
 *         
 *  Exercise 6-3. Write a cross-referencer that prints a list of all words in a document, and for
 *  each word, a list of the line numbers on which it occurs. Remove noise words like ``the,''
 *  ``and,'' and so on.OB
 */


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAXWORD 100

/**
 * @var int line_no - counter for the lines in the input
 */
int line_no = 1;

int flag = 0;

/**
 * @struct struct tnode  - structure that describest a tree that has as content for 
 * each node in the tree - strings
 *      char *word - describes the content for each field
 *      int count - contor for each word containg the number of appearances
 */
struct tnode 
{    
   char *word;
   int count;
   int lines[100];
   struct tnode *left;
   struct tnode *right;
};

/**
 * @fn struct tnode *addtree(struct tnode *, char *);
 * @brief function that adds a new node to the tree
 * @param struct tnode * node - the current tree
 * @param char * word - the content to add the new node
 * @return the new tree
 */
struct tnode *addtree(struct tnode *, char *);

/**
 * @fn void treeprint(struct tnode *);
 * @brief function that prints a tree in a certain format
 * @param struct tnode * node - the current tree to be printed
 */
void treeprint(struct tnode *);

/**
 * @fn int getword(char *, int);
 * @brief function that gets the next word - from the input  
 * @param char * => the variable in which to assign the nu word
 * @param int => tha max length of the word
 * @return 
 * 
 */
int getword(char *, int);


struct tnode *talloc(void);


char *strdup1(char *);

/**
 *  @def BUFSIZE - sets the maximul length of the buffer
 */
#define BUFSIZE 100

/**
 * @var the buffer used for get and ungetch 
 */
char buf[BUFSIZE];int bufp = 0; 

/*next free position in buf */

/* delivers to next char to be 
 * read and gets it out from the buffer */
int getch(void);


/* pushes back one character into the 
 * shared buffer for it can be evaluated again */
void ungetch(int);

/* word frequency count */
int main(void)
{
   struct tnode *root;
   char word[MAXWORD];
   root = NULL;

   while (getword(word, MAXWORD) != EOF)
      if (isalpha(word[0]))
         root = addtree(root, word);
   treeprint(root);

   return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
   int cond;

   if (p == NULL) 
   {
      /* a new word has arrived */
      p = talloc();   
      /* make a new node */
      p->word = strdup1(w);
      p->count = 1;
      p->left = p->right = NULL;
      p->lines[p->count - 1] = flag == 0 ? line_no : line_no - 1;
      flag = 0;
   } 
   else if ((cond = strcmp(w, p->word)) == 0)
   {
      ///if it hasn't already appeared on that line
      if (p->lines[p->count -1] != line_no)
         p->lines[p->count] = flag == 0 ? line_no : line_no - 1;
      flag = 0;
      p->count++;      
   }
   /* repeated word */
   else if (cond < 0)   
      /* less than into left subtree */
      p->left = addtree(p->left, w);
   else 
      /* greater than into right subtree */
      p->right = addtree(p->right, w);

   return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
   int i = 0;
   
   if (p != NULL) 
   {
      treeprint(p->left);
      printf("%4d %s : ", p->count, p->word);
      for ( i = 0; p->lines[i] ;i++)
         printf("%d, ", p->lines[i]);
      printf("\n");
      treeprint(p->right);
   }
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
   return (struct tnode *) malloc(sizeof(struct tnode));
}
   
char *strdup1(char *s)   
{
   char *p;
   p = (char *) malloc(strlen(s)+1); 
   /* +1 for '\0' */
   if (p != NULL)
      strcpy(p, s);
   return p;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
   int c, getch(void);
   void ungetch(int);
   char *w = word;

   while (isspace(c = getch()))
      ;
   if (c == '\n')
   {
      line_no ++;
      while ( (c = getch()) == '\n')
         line_no++;
   }

   if (c != EOF)
      *w++ = c;

   if (!isalpha(c)) 
   {
      *w = '\0';
      return c;
   }

   for ( ; --lim > 0; w++)
      if (!isalnum(*w = getch())) 
      {
        if (*w == '\n')
        {
          line_no ++;
          flag = 1;
        }
        else
            ungetch(*w);
         break;
      }

   *w = '\0';
   if (strlen(word) < 4)
      getword(word, lim);

   return word[0];
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

