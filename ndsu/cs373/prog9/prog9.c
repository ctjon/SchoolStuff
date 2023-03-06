/*
 * Chris Tjon CS373 Program 9 8 December 1993
 * 
 * This program takes a C program as input and substitutes different key words
 * for all its reserved words.  Reserved words that appear in comments or
 * quoted text will not be substituted.  These words will be stored in an
 * input file with the following format.
 * 
 * <reserved word>  <word to substitue>
 * ...
 * $
 * <program source code in which to do the substitution>
 * 
 * Note that the "$" is the terminator of the substitution list.
 * 
 * The syntax for executing this program is: <program name> <infile> <outfile>
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXSTRING 255
#define MAX_TABLE 1024

int construct_table(FILE * infile, char **key_table, char **sub_table);
int in_table(char *target, char **table);
void dump_tables(char **key_table, char **sub_table);
void process_body(FILE * ifile, FILE * ofile, char **key_table, char **sub_table);

void main(int argc, char *argv[])
{
    FILE *input, *output;	/* input and output files */
    char *key_table[MAX_TABLE];	/* array of pointers to key word table */
    char *sub_table[MAX_TABLE];	/* array of pointers to substite word table */

    if (argc != 3)
    {
	fprintf(stderr, "usage: %s <input file> <output file>\n", argv[0]);
	exit(-1);
    }
    if ((input = fopen(argv[1], "r")) == NULL)
    {
	fprintf(stderr, "%s unable to open input file %s\n", argv[0], argv[1]);
	exit(-1);
    }
    if ((output = fopen(argv[2], "w")) == NULL)
    {
	fprintf(stderr, "%s unable to open output file %s\n", argv[0], argv[2]);
	exit(-1);
    }
    if (!construct_table(input, key_table, sub_table))
    {
	fprintf(stderr, "%s unable to create substitution table\n", argv[0]);
	exit(-1);
    }
    process_body(input, output, key_table, sub_table);
    fclose(input);
    fclose(output);
}

int construct_table(FILE * infile, char **key_table, char **sub_table)
/*
 * requires: a valid file pointer and the init of key_table and sub_table
 * modifies: key_table, sub_table
 * effects:  builds key_table and sub_table so that sub_table[i] is related to
 *           key_table[i] as its substitute
 */
{
    int i = 0;
    char buf[MAXSTRING], key_buf[MAXSTRING], sub_buf[MAXSTRING];

    while ((fgets(buf, MAXSTRING, infile)[0] != '$') && !feof(infile))
    {
	sscanf(buf, "%s %s", key_buf, sub_buf);
	key_table[i] = strdup(key_buf);	/* note strdup does malloc for us */
	sub_table[i] = strdup(sub_buf);	/* note strdup does malloc for us */
	i++;
	buf[0] = '\0';
	if (i > MAX_TABLE)
	    return (0);
    }
    return (1);
}

int in_table(char *target, char **table)
/*
 * requires: that table has been initialized
 * modifies: nothing
 * effects:  returns index of the target if found in the table, -1 otherwise
 */
{
    int i = 0;

    while (table[i] != NULL)
    {
	if (strcmp(target, table[i]) == 0)
	    return (i);
	i++;
    }
    return (-1);
}

void dump_tables(char **key_table, char **sub_table)
/*
 * requires: Tables have been initialized
 * modifies: nothing
 * effects:  dumps two tables by corresponding values eg. key_table[index] and
 *           sub_table[index] on a single output line
 */
{
    int index = 0;

    while ((key_table[index] != NULL) && (sub_table[index] != NULL))
    {
	printf("[%s] [%s]\n", key_table[index], sub_table[index]);
	index++;
    }
    printf("dump_tables -> table sizes for this run = %d\n", index);
    if ((key_table[index] != NULL) && (sub_table[index] != NULL))
    {
	fprintf(stderr, "%s\n", "Table sizes do not match - halting");
	exit(-1);
    }
}

void process_body(FILE * ifile, FILE * ofile, char **key_table, char **sub_table)
/*
 * requires: files have been opened and tables have been initialized
 * modifies: ofile
 * effects:  makes the substituion of every keyword in key_table throughout
 *           the remaining text in ifile with the corresponding word in
 *           sub_table and places the result in ofile
 */
{
    int i = 0;			/* counter variable */
    int ccount = 0;		/* counter to track depth of comments */
    int qcount = 0;		/* counter to track depth of quotes */
    char ch;			/* character to be used for input character */
    char nextch;		/* character to be used for input character */
    char lastch;		/* character to be used for input character */
    char word[MAXSTRING];	/* used to assemble word 1 char at a time */
    int word_completed;		/* boolean type int variable - full word? */

    nextch = lastch = ' ';
    while ((ch = getc(ifile)) != EOF)
    {
	if (isalnum(ch))
	{
	    word[i++] = ch;
	    word_completed = 0;
	}
	else if (isspace(ch) || ispunct(ch))
	{
	    word[i] = '\0';
	    word_completed = 1;
	    switch (ch)
	    {
	    case '/':
		if ((nextch = getc(ifile)) != EOF)
		    ungetc(nextch, ifile);
		if ((nextch == '*') && !ccount && (lastch != '*'))
		    ccount++;
		break;
	    case '*':
		if ((lastch != '/') && ccount)
		{
		    if ((nextch = getc(ifile)) != EOF)
			ungetc(nextch, ifile);
		    if (nextch == '/')
			ccount--;
		}
		break;
	    case '"':
		if (!ccount)
		{
		    if (qcount)
			qcount--;
		    else
			qcount++;
		}
		break;
	    }
	    if ((i > 0) && word_completed)
	    {
		if ((in_table(word, key_table) > -1) && !ccount && !qcount)
		    fputs(sub_table[in_table(word, key_table)], ofile);
		else
		    fputs(word, ofile);
		i = 0;
		word[0] = '\0';
	    }			/* if (i > 0 */
	    lastch = ch;
	    fputc(ch, ofile);
	}
    }				/* while */
}
