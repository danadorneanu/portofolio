#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>      /* flags for read and write */
#include <sys/types.h>  /* typedefs */
#include <sys/stat.h>   /* structure returned by stat */
#include <sys/dir.h>   /* local directory structure */
#include <unistd.h>
#include <time.h>

#undef S_IFDIR
#undef S_IFCHR
#undef S_IFBLK
#undef S_IFREG
#undef NAME_MAX
#undef S_IFMT

#define NAME_MAX   14  /* longest filename component; */

typedef struct {       /* portable directory entry */
   long ino;                  /* inode number */
   char name[NAME_MAX+1];     /* name + '\0' terminator */
} myDirent;

typedef struct {       /* minimal myDIR: no buffering, etc. */
   int fd;               /* file descriptor for the directory */
   myDirent d;             /* the directory entry */
} myDIR;

char name[] = "/home/src/";
struct stat stbuf;

myDIR *myopendir(char *dirname);
myDirent *myreaddir(myDIR *dfd);

stat(name, &stbuf);

void myclosedir(myDIR *dfd);
void dirwalk(char *, void (*fcn)(char *));
void fsize(char *);


#define S_IFMT  0160000 /* type of file: */
#define S_IFDIR 0040000 /* directory */
#define S_IFCHR 0020000 /* character special */
#define S_IFBLK 0060000 /* block special */
#define S_IFREG 0010000 /* regular */

#ifndef myDIRSIZ
#define myDIRSIZ 14
#endif
struct mydirent 
{  /* directory entry */
   ino_t d_ino;          /* inode number */
   char d_name[myDIRSIZ]; /* long name does not have '\0' */
};


/* print file name */
int main(int argc, char **argv)
{
    if (argc == 1) /* default: current directory */
         fsize(".");
    else
         while (--argc > 0)
             fsize(*++argv);
    return 0;
}

/* fsize: print the name of file "name" */
void fsize(char *name)
{
   struct stat stbuf;

   if (stat(name, &stbuf) == -1) 
   {
      fprintf(stderr, "fsize: can't access %s\n", name);
      return;
   }

   if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
      dirwalk(name, fsize);
   
   printf("%8ld %s\n", stbuf.st_size, name);
}

#define MAX_PATH 1024
/* dirwalk: apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *))
{
   char name[MAX_PATH];
   myDirent *dp;
   myDIR *dfd;

       if ((dfd = myopendir(dir)) == NULL) 
       {
          fprintf(stderr, "dirwalk: can't open %s\n", dir);
          return;
       }

       while ((dp = myreaddir(dfd)) != NULL) 
       {
          if (strcmp(dp->name, ".") == 0 || strcmp(dp->name, ".."))
             continue;     /* skip self and parent */
          if (strlen(dir)+strlen(dp->name)+2 > sizeof(name))
             fprintf(stderr, "dirwalk: name %s %s too long\n", dir, dp->name);
          else 
          {
             sprintf(name, "%s/%s", dir, dp->name);
             (*fcn)(name);
          }
       }
       myclosedir(dfd);
}

/* myopendir: open a directory for myreaddir calls */
myDIR *myopendir(char *dirname)
{
   int fd;
   struct stat stbuf;
   myDIR *dp;

   if ((fd = open(dirname, O_RDONLY, 0)) == -1 
         || stat(name, &stbuf) == -1 
         || (stbuf.st_mode & S_IFMT) != S_IFDIR
         || (dp = (myDIR *) malloc(sizeof(myDIR))) == NULL)
      return NULL;

   dp->fd = fd;
   return dp;
}

/* myclosedir: close directory opened by myopendir */
void myclosedir(myDIR *dp)
{
   if (dp) 
   {
      close(dp->fd);
      free(dp);
   }
}

/* myreaddir: read directory entries in sequence */
myDirent *myreaddir(myDIR *dp)
{
   struct direct dirbuf; /* local directory structure */
   static myDirent d;       /* return: portable structure */

   while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf))  == sizeof(dirbuf)) 
   {
      if (dirbuf.d_ino == 0) /* slot not in use */
         continue;
      d.ino = dirbuf.d_ino;
      strncpy(d.name, dirbuf.d_name, myDIRSIZ);
      d.name[myDIRSIZ] = '\0'; /* ensure termination */
      return &d;
   }
   return NULL;
}

