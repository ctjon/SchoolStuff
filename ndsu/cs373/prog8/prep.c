/******************************************************************************/
/* PREP.C                                                                     */
/* Written By: Chris Tjon                                                     */
/* For: CS 373 Program #8                                                     */
/* Due: 1 December 1993                                                       */
/******************************************************************************/
/* This is the filter "prep" which splits its text input into words, one word */
/* per line, all alphabetic characters translated to lower case, and puts     */
/* this result on its standard output.                                        */
/******************************************************************************/
/* Use the following to generate your output:                                 */
/* ./prep < ~gammill/373/hmwrk1|sort|uniq -c|sort -n -r|pr -3                 */
/******************************************************************************/

#include <stdio.h>
#include <ctype.h>
#define APOSTROPHE 39

main()
{
    char ch, nextch, lastch = '\0';
    int i = 0;

    while ((ch = getchar()) != EOF)
    {
	if (isdigit(ch)) ch = ' ';
	if (isupper(ch)) ch = tolower(ch);

	/* Handle punctuation at the beginning of a word such as "test" */
	if (isspace(ch))
	{
	    if ((nextch = getchar()) != EOF)
	    {
		if (ispunct(nextch)) nextch = ' ';
		ungetc(nextch, stdin);
	    }
	    ch = ' ';
	}

	/* Handle apostrophe correctly */
	if (ispunct(ch))
	{
	    if (ch == APOSTROPHE)
	    {
		if ((nextch = getchar()) != EOF)
		{
		    if (!isalpha(nextch)) ch = ' ';
		    ungetc(nextch, stdin);
		}
	    }
	    else
		ch = ' ';
	}

	if ((isalpha(ch)) || (ispunct(ch))) putchar(ch);
	if ((isspace(ch)) && (isalpha(lastch))) putchar('\n');
	lastch = ch;
    }
}
