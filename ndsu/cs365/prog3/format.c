/*
   format.c
*/

#define tab 0x09

void DoCommand ();
void DoText ();

#include "doc.h"

/*
   Name:	DoLine Function:
*/
int DoLine (d, LineNo)
doc d;
int LineNo;
{
	char ch;
	char why[80];

	ch = fgetc (stdin);
	if (feof (stdin))
		return TRUE;
	if (ch == '.')
	  {
		  strcpy (why, "");
		  DoCommand (d, why);
		  if (strcmp (why, ""))
			  fprintf (stderr, "%s %d: %s\n", "Line", LineNo, why);
	  }
	else
	  {
		  ungetc (ch, stdin);
		  DoText (d);
	  }
	return FALSE;
}

/*
   Name:	DoCommand(d,err) Function:
*/
void DoCommand (d, err)
doc d;
char *err;
{
	char cmd[80];

	fgets (cmd, 79, stdin);
	cmd[strlen (cmd) - 1] = '\0';
	if (strlen (cmd) == 0)
		strcpy (err, "missing command");
	else if (!strcmp (cmd, "nf"))
		SetNoFill (d);
	else if (!strcmp (cmd, "fi"))
		SetFill (d);
	else if (!strcmp (cmd, "br"))
		BreakLine (d);
	else
		sprintf (err, "%s - Not a command", cmd);
}

/*
   Name:	DoText Function:
*/
void DoText (d)
doc d;
{
	register int i;
	char c, next;
	char endword[80];

	c = fgetc (stdin);
	if (c == EOL)
	  {
		  SkipLine (d);
		  return;
	  }
	if ((c == ' ') || (c == tab))
		BreakLine (d);
	for (;;)
	  {
		  if (c == EOL)
		    {
			    break;
		    }
		  if (c == ' ')
			  DocAddSpace (d);
		  else if (c == tab)
			  DocAddTab (d);
		  else
		    {
			    i = 0;
			    endword[i++] = c;
			    for (;;)
			      {
				      next = fgetc (stdin);
				      if (next == EOL || next == ' ' || next == tab)
					{
						endword[i] = '\0';
						ungetc (next, stdin);
						break;
					}
				      else
					      endword[i++] = next;
			      }
			    DocAddWord (d, endword);
		    }
		  c = fgetc (stdin);
	  }
	AddNewLine (d);
}
