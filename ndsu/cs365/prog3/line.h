#ifndef __LINEH__
#define __LINEH__

#include <stdio.h>

/*
   line.h Structure definitions

line = data type is Create, AddWord, AddSpace, AddTab, Justify, Output, Clear

Overview: A line is a mutable line of text consisting of the characters
   corresponding to words, tabs, and spaces.  Operation Justify justifies the
   line to a given length, and the line is written to stdout.  The output can
   then be redirected into a file.
*/

#define MAXWORDLEN 30
#define MAXLINELEN 60
#define MAXTABWIDTH 8

#ifndef TRUE
#define TRUE 1
#define FALSE 0
typedef int boolean;

#endif

#ifndef NULL
#define NULL 0L
#endif


typedef enum
{
	WORD, SPACE, TAB
} datatype;


typedef struct item
{
	datatype Form;
	union
	{
		char Word[MAXWORDLEN];
		int Count;
	} Data;
} item;

typedef struct linerec
{
	int Length;
	int RightTab;
	int Items;
	item Data[MAXLINELEN];
} linerec;

typedef linerec *line;

/*
   Function Declarations
*/




#endif				/* __FORMH__ */
