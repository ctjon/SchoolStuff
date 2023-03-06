/*
   doc.c
*/

void BreakLine ();
void OutputLine ();
void StartPage ();

#include "doc.h"

/*
   Name:	CreateDoc Function:	Cteate a new document starting on
   page 1 in fill mode
*/
doc CreateDoc ()
{
	doc d;

	if ((d = (doc) malloc (sizeof (docrec))) == NULL)
		perror ("CreateDoc"), exit (1);
	d->Line = (line) CreateLine ();
	d->Fill = TRUE;
	d->Right = TRUE;
	d->LineNum = MAXLINES;
	d->PageNum = 0;
	return d;
}

/*
   Name:	DocAddWord Function:	Add a word to the document
*/
void DocAddWord (d, word)
doc d;
char *word;
{
	if ((d->Fill == TRUE) && (LineLength (d->Line) > 0))
	  {
		  if ((LineLength (d->Line) + strlen (word)) > MAXLINELEN)
		    {
			    Justify (d->Line, MAXLINELEN, d->Right);
			    d->Right = !d->Right;
			    OutputLine (d);
		    }
	  }
	AddWord (d->Line, word);
}

/*
   Name:	DocAddSpace Function:	Adds a space to a document
*/
void DocAddSpace (d)
doc d;
{
	AddSpace (d->Line);
}

/*
   Name:	DocAddTab Function:	Add a tab to a document
*/
void DocAddTab (d)
doc d;
{
	AddTab (d->Line);
}

/*
   Name:	AddNewLine Function:	Adds an end-of-line terminator
*/
void AddNewLine (d)
doc d;
{
	if (d->Fill == FALSE)
		OutputLine (d);
	else
		AddSpace (d->Line);
}

/*
   Name:	SkipLine Function:	Adds an empty line to d
*/
void SkipLine (d)
doc d;
{
	BreakLine (d);
	OutputLine (d);
}

/*
   Name:	BreakLine Function:	Adds a line break to d
*/
void BreakLine (d)
doc d;
{
	if (LineLength (d->Line) > 0)
		OutputLine (d);
}

/*
   Name:	SetFill Function:	Adds a line break to d, causes a fill
   mode to be set
*/
void SetFill (d)
doc d;
{
	BreakLine (d);
	d->Fill = TRUE;
}

/*
   Name:	SetNoFill Function:	Adds a line break to d, causes nofill
   mode
*/
void SetNoFill (d)
doc d;
{
	BreakLine (d);
	d->Fill = FALSE;
}

/*
   Name:	Terminate Function:	finishes write d and returns all
   system resources
*/
void Terminate (d)
doc d;
{
	BreakLine (d);
	FreeLine (d->Line);
}

/*
   Name:	OutputLine Function:	a line is written to the output file
*/
void OutputLine (d)
doc d;
{
	register int i;

	if (d->LineNum == MAXLINES)
		StartPage (d);
	else
		d->LineNum++;
	if (LineLength (d->Line) > 0)
	  {
		  for (i = 0; i < LEFTMARGIN; i++)
			  fputc (' ', stdout);
		  DumpLine (d->Line);
		  ClearLine (d->Line);
	  }
}

/*
   Name:	StartPage Function:	Outputs a page header
*/
void StartPage (d)
doc d;
{
	int i;

	d->LineNum = 1;
	d->PageNum++;
	if (d->PageNum > 0)
		fputc (FF, stdout);
	fputc (LF, stdout);
	fputc (LF, stdout);
	for (i = 0; i < LEFTMARGIN; i++)
		fputc (' ', stdout);
	printf ("Page %d\n\n\n", d->PageNum);
}
