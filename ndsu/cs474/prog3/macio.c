/* ------------------------------------------- */
/* Macro IO                                    */
/* ------------------------------------------- */
#include "macro.h"

int Depth = 0;
/*----< Procedure Process File >----------------------------------------------+
 | Strips out the file name to include given a pointer to the pointer pointing|
 | to the current character in the macro being expanded.  If *in = null then  |
 | the current input file is used.  If the depth < 4 processfile assigns the  |
 | current value of the file pointer to a local variable and assigns the file |
 | pointer to the newly opened include file.  It then calls processchar to    |
 | process this file.  When processchar returns the file pointer is reset to  |
 | the old value and the function returns.                                    |
 +----------------------------------------------------------------------------*/
void ProcessFile(in)
char **in;
{
    FILE *f;
    char t, fname[80];
    register int i = 0;
    t = nxtchar(*in);
    while ((fname[i++] = nxtchar(*in)) != t);
    fname[i - 1] = '\0';
    if (++Depth > 3)
	fprintf(stdout, "\ncannot open fifth level file %s\n", fname);
    else
    {
	f = FileIn;
	if ((FileIn = fopen(fname, "r")) == NULL)
	{
	    printf("%s %s\n", "Error - Unable to open", fname);
	    perror("");
	    return;
	}
	ProcessChar(NULL);
	fclose(FileIn);
	FileIn = f;
    }
    Depth--;
}
