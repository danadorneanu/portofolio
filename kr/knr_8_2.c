/*! \file knr_8_2.c
 * \brief Rewrite myfopen and _fillbuf with fields instead of explicit bit operations.
 * Compare code size and execution speed.
 * */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/*!
 * We undef the primitives that we w'll redefine
 * */
#undef NULL
#undef BUFSIZ
#undef stdin
#undef stdout
#undef stderr
#undef getc
#undef putc

/*!
 * RW for owner, group, others 
 * */
#define PERMS 0666    

#define NULL       0
#define EOF        (-1)
#define BUFSIZ     1024

/*!
 * max #files open at once 
 * */
#define  OPEN_MAX   20    

/*!
 * We define the structure for the myFILE type
 * */
typedef struct _iobuf {

   /*!
    * characters left 
    * */
   int cnt;

   /* 
    * next character position 
    * */
   char *ptr;

   /* 
    * location of buffer 
    * */
   char *base;      

   /*!
    * mode of file acces
    * */
   int flag;         

   /* 
    * the file descriptor
    * */
   int fd;           

} myFILE;

extern myFILE _iob[OPEN_MAX];

#define stdin    (&_iob[0])
#define stdout   (&_iob[1])
#define stderr   (&_iob[2])

/*!
 * define the flags for the modes of opening a file
 * */
enum _flags  {
   /* 
    * file open for reading 
    * */
   _READ    = 01,    

   /* 
    * file open for writing 
    * */
   _WRITE   = 02,   

   /* 
    * file is unbuffered 
    * */
   _UNBUF   = 04,    

   /* 
    * EOF has occurred on this file 
    * */
   _EOF     = 010,   

   /* 
    * error occurred on this file 
    * */
   _ERR     = 020    
};

int _fillbuf(myFILE *);
int _flushbuf(int, myFILE *);

#define feof(p)      (((p)->flag & _EOF) != 0)
#define ferror(p)    (((p)->flag & _ERR) != 0)
#define fileno(p)    ((p)->fd)
#define getc(p)    (--(p)->cnt >= 0 \
                      ? (unsigned char) *(p)->ptr++ : _fillbuf(p))

#define putc(x,p) (--(p)->cnt >= 0 \
                      ? *(p)->ptr++ = (x) : _flushbuf((x),p))

#define getchar()  getc(stdin)
#define putcher(x) putc((x), stdout)

myFILE _iob[OPEN_MAX] = 
   {    
   /* 
    * stdin, stdout, stderr 
    * */
   { 0, (char *) 0, (char *) 0, _READ, 0 },
   { 0, (char *) 0, (char *) 0, _WRITE, 1 },
   { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
   };

/*!
 * \fn myFILE *myfopen(char *name, char *mode)
 * \brief this function opens the file whose name is specified by the parameter name and allows on it the 
 * operations that are specified in the mode string
 * \param name - specifies the name of the file to open
 * \param mode - specifies the allowed operations on the file ("r" , "w", "a" )
 */
myFILE *myfopen(char *name, char *mode)
{
   int fd;
   myFILE *fp;

   if (*mode != 'r' && *mode != 'w' && *mode != 'a')
      return NULL;

   /* 
    * found free slot 
    * */
   for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
      if ( (fp->flag != _READ && fp->flag !=  _WRITE) == 0)
         break;        

   /* 
    * no free slots 
    * */
   if (fp >= _iob + OPEN_MAX)  
      return NULL;

   if (*mode == 'w')
      fd = creat(name, PERMS);
   else if (*mode == 'a') 
   {
      if ((fd = open(name, O_WRONLY, 0)) == -1)
         fd = creat(name, PERMS);
      lseek(fd, 0L, 2);
   } 
   else
      fd = open(name, O_RDONLY, 0);

   /* 
    * couldn't access name 
    * */
   if (fd == -1)         
      return NULL;

   fp->fd = fd;
   fp->cnt = 0;
   fp->base = NULL;
   fp->flag = (*mode == 'r') ? _READ : _WRITE;
   
   return fp;
}

/*!
 * \fn int _fillbuf(myFILE *fp)
 * \brief _fillbuf - allocate and fill input buffer 
 * \param myFILE *fp - 
 * \param 
 * */
int _fillbuf(myFILE *fp)
{
   int bufsize;

   if ((fp->flag&(_READ|_EOF|_ERR)) != _READ)
      return EOF;
   bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
   if (fp->base == NULL)     /* no buffer yet */
      if ((fp->base = (char *) malloc(bufsize)) == NULL)
         return EOF;       /* can't get buffer */
   fp->ptr = fp->base;
   fp->cnt = read(fp->fd, fp->ptr, bufsize);

   if (--fp->cnt < 0) 
   {
      if (fp->cnt == -1)
         fp->flag |= _EOF;
      else
         fp->flag |= _ERR;
      fp->cnt = 0;

      return EOF;
   }

   return (unsigned char) *fp->ptr++;
}

int main(int argc, char *argv[])
{
   int ret = 0;
   int c = 0;
   myFILE  *fp;


   

   /// no args; copy standard input 
   if (argc != 2 )       
      printf("\nerror:\n\t correct usage: ./exec_file f1 ");
   else
      while (--argc > 0)
         if ((fp =myfopen(*++argv, "r")) == NULL) 
         {
            printf("\nerror:\n\t: can't open %s\n", *argv);
            exit(1);
         } 
         else 
         {
            while ( (c = getc(fp)) != EOF )
               putchar(c);
         }


   if (ferror(stdout)) 
   {
      printf("\nerror\n\t: error writing stdout\n");
      exit(2);
   }

   return ret;
}
