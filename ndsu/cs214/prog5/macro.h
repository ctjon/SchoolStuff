/* ------------------------------------------- */
/* LIMP - Language Independent Macro Processor */
/* HEADER FILE 				       */
/* ------------------------------------------- */
#include <stdio.h>
extern memset();

extern FILE *FileIn;

#define nxtchar(x) (((x)!=NULL) ? (*((x)++)) : (fgetc(FileIn)))
/* conditional define-returns next character in macro string or next 
   character in current input file if x = null                        */

/* PROTOTYPES */
void ProcessChar();
void ProcessFile();
