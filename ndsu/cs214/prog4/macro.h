/* ------------------------------------------- */
/* LIMP - Language Independent Macro Processor */
/* HEADER FILE 				       */
/* ------------------------------------------- */
#include <stdio.h>
extern memset();

typedef struct macro{
  char Label,Data[255];
  int  pos;
  struct macro *Next;
} MACRO;
extern FILE *FileIn;

#define nxtchar(x) ((x)!=NULL ? ((x)->Data[(x)->pos++]) : (fgetc(FileIn)))

void ProcessChar();
void ProcessFile();
