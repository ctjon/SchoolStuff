/* ------------------------------------------- */
/* LIMP - Language Independent Macro Processor */
/* ------------------------------------------- */
#include "macro.h"
MACRO *MacroStack = NULL;
FILE *FileIn=stdin;

#define WriteChar(c) (fputc((c),stdout))

MACRO *LocateMacro(ch)
char ch;
{
  MACRO *temp=MacroStack;

  while((temp != NULL) && (temp->Label != ch)) temp = temp->Next;
  if (temp != NULL) temp->pos = 0;
  return temp;
}


void CreateMacro(in)
MACRO *in;
{
  MACRO *temp=MacroStack;
  register int i=0;
  char c,t;

  t = nxtchar(in);
  temp = (MACRO *)malloc(sizeof(MACRO));
  temp->Label = nxtchar(in);
  memset(temp->Data,'\0',255);
  temp->Next = MacroStack;
  temp->pos=0;
  MacroStack = temp;
  if (t != '='){
    while ((c = nxtchar(in)) != t) temp->Data[i++] = c;
    temp->Data[i] = EOF;
  } else{
    for (;i<3;i++) temp->Data[0] = (temp->Data[0]*8)+(nxtchar(in)-'0');
    temp->Data[1] = EOF;
  }
}

void ProcessChar(in)
MACRO *in;
{
  char ch,c;
  MACRO *temp;

  while ((ch = nxtchar(in)) != EOF){
    switch(ch){
      case '$': switch((ch = nxtchar(in))){
                  case '$': WriteChar('$'); break;
                  case '0': if (LocateMacro(ch) == NULL)
                              CreateMacro(in);
                            break;
                  case '1': while (nxtchar(in) != '\n'); break;
                  case '%': if ((temp = LocateMacro(ch)) == NULL){
                              c = fgetc(FileIn);
                              if ((temp = LocateMacro(c)) != NULL){
                                ProcessChar(temp);
                              } else {
                  fprintf(stdout,"\n       Macro Call $%% undefined\n");
                                WriteChar(c);
                              }
                            }else
                              ProcessChar(temp);
                            break;
                  default : if ((temp = LocateMacro(ch)) != NULL){
                              ProcessChar(temp);
                            } else 
                  fprintf(stdout,"\n       Macro Call $%c undefined\n",ch);
                } break;
      case '%': if (in != NULL) { WriteChar(fgetc(FileIn)); break; }
      default : WriteChar(ch);
    }
  }
}


main()
{

  ProcessChar(NULL);
}
