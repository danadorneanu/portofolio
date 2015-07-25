/** @file knr_8_3.c
 * @brief Design and write _myflushbuf, myfflush, myfclose 
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * We undef the primitives that we will than redefine
 */
#undef NULL
#undef BUFSIZ
#undef stdin
#undef stdout
#undef stderr
#undef getc
#undef putc

/**
 * RW for owner, group, others 
 */
#define PERMS 0666    

#define NULL       0
#define EOF        (-1)
#define BUFSIZ     1024

/**
 * max #files open at once 
 */
#define  OPEN_MAX   20    

/**
 * We define the structure for the myFILE type
 */
typedef struct _iobuf {

   /**
    * characters left 
    * */
   int cnt;

   /** 
    * next character position 
    * */
   char *ptr;

   /** 
    * location of buffer 
    * */
   char *base;      

   /**
    * mode of file acces
    * */
   int flag;         

   /** 
    * the file descriptor
    * */
   int fd;           

} myFILE;

/**
 * myFILE _iob[OPEN_MAX] - the file where 
 * to put the input/output in binary format
 */
extern myFILE _iob[OPEN_MAX];

#define stdin    (&_iob[0])
#define stdout   (&_iob[1])
#define stderr   (&_iob[2])

/**
 * define the flags for the modes of opening a file
 */
enum _flags {

   /** 
    * file open for reading 
    */
   _READ    = 01,    

   /**
    * file open for writing 
    */
   _WRITE   = 02,   

   /**
    * file is unbuffered 
    */
   _UNBUF   = 04,    

   /**
    * EOF has occurred on this file 
    */
   _EOF     = 010,   

   /**
    * error occurred on this file 
    */
   _ERR     = 020    
};

/**
 * @fn int _fillbuf(myFILE *fp)
 * @brief _fillbuf - allocate and fill input buffer 
 * @param myFILE *fp - 
 * @param 
 */
int _fillbuf(myFILE *);

/**
 * @fn int _myflushbuf(int c, myFILE *fp)
 * @brief _myflushbuf - is called by putchar when the buffer is full
 * @param myFILE *fp - the file descriptor correcponding the to where to put the output
 * @param int c - the ascii code of the just read character 
 */
int _myflushbuf(int, myFILE *);

/**
 * @fn int myfflush (myFILE *fp)
 * @brief 
 * @param
 */
int myfflush(myFILE *fp);

/**
 * @fn int myfclose(myFILE *fp);
 *
 * @brief this function closes a file using its file descriptor
 *
 * @param name - specifies the name of the file to open
 * @param mode - specifies the allowed operations on the file ("r" , "w", "a" )
 */
int myfclose(myFILE *fp);

/**
 * @fn myFILE *myfopen(char *name, char *mode)
 * @brief this function opens the file whose name is specified by the parameter name and allows on it the 
 * operations that are specified in the mode string
 *
 * @param name - specifies the name of the file to open
 * @param mode - specifies the allowed operations on the file ("r" , "w", "a" )
 */
myFILE *myfopen(char *name, char *mode);

#define feof(p)      (((p)->flag & _EOF) != 0)
#define ferror(p)    (((p)->flag & _ERR) != 0)
#define fileno(p)    ((p)->fd)
#define getc(p)    (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))

#define putc(x,p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _myflushbuf((x),p))

#define getchar()  getc(stdin)
#define putchar(x) putc((x), stdout)

myFILE _iob[OPEN_MAX] = {    
   /**
    * stdin, stdout, stderr 
    */
   { 0, (char *) 0, (char *) 0, _READ, 0 },
   { 0, (char *) 0, (char *) 0, _WRITE, 1 },
   { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
   };


int main(int argc, char *argv[])
{
   int ret = 0;
   int c = 0;
   myFILE  *fp_in = NULL, *fp_out = NULL;

   fp_out = myfopen("test", "w");

   /**
    * no args; copy standard input 
    */
   if (argc != 2) 
      printf("\nerror:\n\t correct usage: ./exec_file f1 ");
   else
      while (--argc > 0)
         if ((fp_in = myfopen(*++argv, "r")) == NULL) 
         {
            printf("\nerror:\n\t: can't open %s\n", *argv);
            exit(1);
         } 
         else 
            while ( (c = getc(fp_in)) != EOF)
               _myflushbuf(c, fp_out);

   myfclose(fp_in);

   return ret;
}

int _fillbuf(myFILE *fp)
{
   int bufsize;

   if ((fp->flag&(_READ|_EOF|_ERR)) != _READ)
      return EOF;
   bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
   /* no buffer yet */

   if (fp->base == NULL)     
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

int _myflushbuf(int c, myFILE *fp)
{
   //int ret = 0;
   int bufsize = 0;
   int num_written = 0;
   unsigned char uc = c;


   if ((fp->flag & (_WRITE|_EOF|_ERR)) != _WRITE)
      return EOF;

   bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

   /**
    * no buffer yet 
    */
   if (fp->base == NULL) 
   {
      /** 
       * if we couldn't allocate any memory
       */
      if ((fp->base = (char *) malloc(bufsize)) == NULL)
         fp->flag |= _UNBUF;
      else 
      {
         /**
          *  we assign the first character to it's place
          *  and we set the maximum size til we have to flush
          */
         fp->ptr = fp->base;
         fp->cnt = BUFSIZ - 1;
      }
   }

   /**
    *  
    */
   if (fp->flag & _UNBUF)
   {
      /**
       * if unbuffered than write
       */
      fp->ptr = fp->base = NULL;
      fp->cnt = 0;

      if (c == EOF)
         return EOF;

      num_written =  write(fp->fd, &uc, 1);
      bufsize = 1;
   } 
   else
   {
      /*
       * adding a new character
       */
      if (c != EOF)
         *(fp -> ptr++) = uc;

      /*
       * 
       */
      bufsize = (int) (fp->ptr - fp->base);
      num_written = write(fp->fd, fp->base, bufsize);
      fp->ptr = fp->base;
      fp->cnt =BUFSIZ - 1;
   } 

   if (num_written == bufsize)
      return c;
   else
   {
      fp->flag |= _ERR;
      return EOF;
   }
}


int myfflush (myFILE *fp)
{
   int ret = 0;
   int i = 0;
   
   if (fp == NULL)
   {
      for (i = 0; i < OPEN_MAX; i++)
      {
         /**
          * if the given stream was open for writing 
          * and the last i/o operation was an output operation
          * any unwritten data in the output buffer is written to the file
          */
         if (((_iob + i)->flag & _WRITE) && (myfflush(_iob + i) == -1))
            ret = EOF;
      }
   }
   else
   {
      /**
       *  
       */
      if ((fp->flag&_WRITE) == 0)
         return EOF;
      _myflushbuf(EOF, fp);
      if (fp->flag&_ERR)
         ret = EOF;
   }
   
   return ret;
}


/**
 * @fn myFILE *myfopen(char *name, char *mode)
 * @brief this function opens the file whose name is specified by the parameter name and allows on it the 
 * operations that are specified in the mode string
 * @param name - specifies the name of the file to open
 * @param mode - specifies the allowed operations on the file ("r" , "w", "a" )
 */
myFILE *myfopen(char *name, char *mode)
{
   int fd;
   myFILE *fp;

   if (*mode != 'r' && *mode != 'w' && *mode != 'a')
      return NULL;

   /**
    * found free slot 
    */
   for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
      if ( (fp->flag != _READ && fp->flag !=  _WRITE) == 0)
         break;        

   /** 
    * no free slots 
    */
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

   /**
    * couldn't access name 
    */
   if (fd == -1)         
      return NULL;

   fp->fd = fd;
   fp->cnt = 0;
   fp->base = NULL;
   fp->flag = (*mode == 'r') ? _READ : _WRITE;
   
   return fp;
}

int fseek(myFILE *fp, long offset, int whence)
{
   if ((fp->flag & _UNBUF) == 0 && (base != NULL))
   {
      /**
       * deal with buffering 
       */
      if (fp->flag & _WRITE) 
      {
         /*
          * writing, so flush buffer 
          */
         myfflush(fp);
      } 
      else if (fp->flag & _READ) 
      {
         /* 
          * reading, so trash buffer 
          */
         fp->cnt = 0;
         
         fp->ptr = f->base;
      }
   }

   return (lseek(fp->fd, offset, whence) < 0);
}


int myfclose(myFILE *fp)
{
   int fd = 0;
  
   /**
    * there is nothing to be closed
    */
   if (fp == NULL)
      return -1;

   /**
    * flush everything that is left in my file before close it
    */
   fd = fp->fd;
   myfflush(fp);
   fp->cnt = 0;
   fp->ptr = NULL;

   /**
    * free the location of the buffer too
    */
   if (fp->base != NULL)
      free(fp->base);

   /**
    * 
    */
   fp->base = NULL;
   fp->flag = 0;
   fp->fd = -1;
   
   return close(fd);
}

