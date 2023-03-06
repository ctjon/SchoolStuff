
/*
   main.c
*/
#include <signal.h>
#include "doc.h"

void abort ()
{
	printf ("Signal caught... aborting\n");
	exit (1);
}

int main ()
{
	doc d;
	int LineNo = 0;

	sigvec (SIGSEGV, abort);
	d = (doc) CreateDoc ();
	do
	  {
		  LineNo++;
	  }
	while (DoLine (d, LineNo) == FALSE);
	Terminate (d);
}
