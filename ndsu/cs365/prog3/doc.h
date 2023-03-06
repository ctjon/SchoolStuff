#ifndef __DOCH__
#define __DOCH__

#include "line.h"

/*
   doc.h Structure defintions
*/

#define MAXLINES 50
#define LEFTMARGIN 10
#define LF	'\n'
#define FF	'\x0C'
#define EOL	'\n'

typedef struct docrec
{
	line Line;
	boolean Fill, Right;
	int LineNum, PageNum;
} docrec;

typedef struct docrec *doc;

#endif				/* __DOCH__ */
