#include "line.h"

/*
   Static functions
*/
static boolean FindJustifySpace ();
static void EnlargeSpaces ();
static void CountSpaces ();

/*
   Name: 	CreateLine Function:	Creates and returns a new empty line
*/
line CreateLine ()
{
	line l;

	if ((l = (line) malloc (sizeof (linerec))) == NULL)
		perror ("NewLine"), exit (1);
	l->Length = 0;
	l->RightTab = 0;
	l->Items = 0;
	return l;
}

/*
   Name:	ClearLine; Function:	Reinitializes line l to use again
*/
line ClearLine (l)
line l;
{
	if (l == NULL)
		return CreateLine ();
	l->Length = 0;
	l->Items = 0;
	l->RightTab = 0;
	return l;
}

/*
   Name:	FreeLine; Function:	Release system resources associated
   with a line
*/
void FreeLine (l)
line l;
{
	free (l);
}

/*
   Name:	LineLength Function:	Return length of current line
*/
int LineLength (l)
line l;
{
	return l->Length;
}

/*
   Name:	DumpLine Function:	Dump out line to standard output
*/
void DumpLine (l)
line l;
{
	register int i, j;

	for (i = 0; i < l->Items; i++)
	  {
		  switch (l->Data[i].Form)
		    {
		    case WORD:
			    printf ("%s", l->Data[i].Data.Word);
			    break;
		    case TAB:
		    case SPACE:
			    for (j = 0; j < l->Data[i].Data.Count; j++)
				    fputc (' ', stdout);
			    break;
		    }
	  }
	fputc ('\n', stdout);
}

/*
   Name:	AddWord Function:	Add a word to the end of a line
*/
void AddWord (l, word)
line l;
char *word;
{
	strcpy (l->Data[l->Items].Data.Word, word);
	l->Data[l->Items].Form = WORD;
	l->Items++;
	l->Length += strlen (word);
}

/*
   Name:	AddSpace Function: 	Append a space to the end of a line
*/
void AddSpace (l)
line l;
{
	l->Length++;
	if (l->Items > 0 && l->Data[l->Items - 1].Form == SPACE)
		l->Data[l->Items - 1].Data.Count++;
	else
	  {
		  l->Data[l->Items].Data.Count = 1;
		  l->Data[l->Items].Form = SPACE;
		  l->Items++;
	  }
}

/*
   Name:	AddTab Function:	Append a Tab to the end of line Tab
   is 1 to 8 spaces
*/
void AddTab (l)
line l;
{
	register int num;

	num = MAXTABWIDTH - (l->Length % MAXTABWIDTH);
	l->Length += num;
	l->Data[l->Items].Form = TAB;
	l->Data[l->Items].Data.Count = num;
	l->RightTab = l->Items;
	l->Items++;
}

/*
   Name:	Justify Function:	Justifies l as described in the
   specifications of the original format.
*/
void Justify (l, len, right)
line l;
int len;
boolean right;
{
	register int diff;
	int first;

	if (l->Data[l->Items - 1].Form == SPACE)
	  {
		  l->Length -= (l->Data[l->Items - 1].Data.Count);
		  l->Items--;
	  }
	if (l->Length < len)
	  {
		  diff = len - l->Length;
		  first = 0;
		  if (FindJustifySpace (l, &first) == TRUE)
		    {
			    EnlargeSpaces (l, first, diff, right);
		    }
	  }
}

/*********************************
 *      STATIC FUNCTIONS
 *********************************/

/*
   Name: 	FindJustifySpace Function:	Return index in line data of
   first justifiable space, return FALSE if none available
*/
static boolean FindJustifySpace (l, p)
line l;
int *p;
{
	int pos;

	if (l->Items == 0)
		return FALSE;
	pos = l->RightTab + 1;
	if ((pos < l->Items) && (l->Data[pos].Form == SPACE))
		pos++;
	while ((pos < l->Items) && (l->Data[pos].Form != SPACE))
		pos++;
	*p = pos;
	return (pos < l->Items);
}

/*
   Name:	EnlargeSpaces Function:	Distribute diff spaces between first
   and last space in data.
*/
static void EnlargeSpaces (l, first, diff, right)
line l;
int first, diff;
boolean right;
{
	register int neach, nextra, by, i;
	int nspaces = 0, last = 0;

	CountSpaces (l, first, &nspaces, &last);
	if (nspaces <= 0)
		return;
	by = 1;
	if (right == TRUE)
	  {
		  by = -1;
		  i = first;
		  first = last;
		  last = i;
	  }
	neach = diff / nspaces;
	nextra = diff % nspaces;
	i = first;
	do
	  {
		  if (l->Data[i].Form == SPACE)
		    {
			    l->Data[i].Data.Count = l->Data[i].Data.Count + neach;
			    if (nextra > 0)
			      {
				      l->Data[i].Data.Count++;
				      nextra--;
			      }
		    }
		  i += by;
	  }
	while (i != last + by);
	l->Length += diff;
}

/*
   Name:	CountSpaces Function:	Returns a count of spaces subject to
   justification and the index in the l->Data of the last such space
*/
static void CountSpaces (l, beg, cnt, idx)
line l;
int beg;
int *cnt, *idx;
{
	register int i;

	for (i = beg; i < l->Items; i++)
		if (l->Data[i].Form == SPACE)
		  {
			  (*cnt)++;
			  *idx = i;
		  }
}
