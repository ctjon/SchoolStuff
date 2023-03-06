/*+------------------------------------------------------------------------+ 
  | LIMP - Language Independent Macro Processor                            |
  |                                                                        |
  | Written by: Christopher C. Tjon                                        |
  | For Dr. Erickson's CS214                                               |
  | 18 May 1990                                                            |
  |                                                                        |
  | The instructions for this programming assignment can be found in the   |
  | /class/ndsu/214/Info in the files prog4 and prog5.  Test input and     |
  | examples can be found in the /class/ndsu/214/Info/mactst directory     |
  |                                                                        |
  | Capabilities of Macroprocessor:                                        |
  |               1) Nested Macros                                         |
  |               2) Macro substitution                                    |
  |               3) Include files can be loaded to a maximum depth of 4   |
  |               4) Special Flag characters may be redefined through      |
  |                      command line arguments                            |
  |               5) Additional features may be added with minimal changes |
  |                                                                        |
  +------------------------------------------------------------------------+*/
 
#include "macro.h"
/* used to link macro.c and macio.c                                         */

char Macro[128][255];  /* define the array called Macro 128x255             */

char err1[]="\n      Macro Call $",err2[]=" undefined.\n";
/* error output messages                                                    */

char flag[6]= { '$','0','1','2','%','=' };
/* flags for special characters which indicate a macro operation            */

FILE *FileIn=stdin;
/* Set input file to standard input by default at start                     */

#define WriteChar(c) (fputc((c),stdout))
/* Use define instead of procedure to save on number of lines               */

#define Defined(c)   (Macro[(c)][0]) 
/* Defined: boolean variable to determine if a macro is already defined     */

#define MACRO(c,p)   (Macro[(c)][(p)])
/* MACRO returns the position p of macro defined as c                       */

/*----< Procedure Create Macro >--------------------------------------------+/
 | When a call to create macro occurs in the input file (ie $0) this        |
 | function strips the definition out of the input and stores under the     |
 | defined name in the macro array                                          |
 +--------------------------------------------------------------------------*/

void CreateMacro(in)
char **in;
{
  register char c,t,i=0;
  t = nxtchar(*in);
  c = nxtchar(*in);
  if (t != flag[5]) while ((MACRO(c,i++) = nxtchar(*in)) != t); 
  else{
    for (i=0;i<3;i++) MACRO(c,0) = (MACRO(c,0)<<3)+(nxtchar(*in)-'0');
    i--; }
  MACRO(c,i-1) = EOF;
}

/*----< Procedure Process Character >---------------------------------------+
 | recursive procedure which expands the macros and terminates when an EOF  |
 | is read.  Called recursively each time a macro is called or a new file   |
 | is used for input                                                        |
 | Input to the function is a character pointer pointing to a macro string  |
 | If in = null characters are retrieved from the current input file        |
 | all characters output are directed to stdout                             |
 +--------------------------------------------------------------------------*/
void ProcessChar(in)
char *in;
{
  char ch;

  while ((ch = nxtchar(in)) != EOF){
    if (ch == flag[0]){
      ch = nxtchar(in);
      if (ch == flag[0]) WriteChar('$'); 
      else if ((ch == flag[1]) && (!Defined(ch))) CreateMacro(&in); 
      else if (ch == flag[2]) while(nxtchar(in) != '\n');
      else if (ch == flag[3]) ProcessFile(&in);
      else if (ch == flag[4]) 
        if ((!Defined(ch)) && (!Defined(ch=fgetc(FileIn))))
          fprintf(stdout,"%s%c%s%c",err1,flag[4],err2,ch);
        else ProcessChar(&MACRO(ch,0));
      else if (Defined(ch)) ProcessChar(&MACRO(ch,0));
      else fprintf(stdout,"%s%c%s",err1,ch,err2);
      continue; }
    else if (ch == flag[4])
      if (in != NULL) ch = fgetc(FileIn);
    WriteChar(ch); }
}

/*----< Main Procedure >----------------------------------------------------*/

main(argc,argv)
int argc;
char *argv[];
{
  register int i;
  memset(Macro,'\0',sizeof(char)*128*255);
  while ((--argc > 0) && (argv[argc][0] == '-')){
    for (i=0;i<6;i++)
      if (flag[i] == argv[argc][1]){
        flag[i] = argv[argc][2];
        break; } }
  ProcessChar(NULL);
}
