#include <stdio.h>
#include "soundex.h"

char buf[80];

char *soundex_rep_of (word)
/*-----------------------------------------------------------------------------+
|-requires - the tree has been initialized                                     |
|-modifies - nothing                                                           |
|-effects  - returns the soundex_rep of *word                                  |
+-----------------------------------------------------------------------------*/
char *word;

{
	register int i = 1, t = 1;

	strcpy (buf, word);
	while (word[i] != '\0')
	  {
		  switch (word[i])
		    {
		    case 'a':
		    case 'e':
		    case 'h':
		    case 'i':
		    case 'o':
		    case 'u':
		    case 'w':
		    case 'y':
			    break;
		    case 'b':
		    case 'f':
		    case 'p':
		    case 'v':
			    buf[t++] = '1';
			    break;
		    case 'c':
		    case 'g':
		    case 'j':
		    case 'k':
		    case 'q':
		    case 's':
		    case 'x':
		    case 'z':
			    buf[t++] = '2';
			    break;
		    case 'd':
		    case 't':
			    buf[t++] = '3';
			    break;
		    case 'l':
			    buf[t++] = '4';
			    break;
		    case 'm':
		    case 'n':
			    buf[t++] = '5';
			    break;
		    case 'r':
			    buf[t++] = '6';
			    break;
		    default:
			    printf ("%s %s %s\n", "SOUNDEX error", buf[i],
				    "is not an alpha character");
			    break;
		    }
		  i++;
	  }
	buf[4] = '\0';
	buf[t] = '\0';

	return (buf);
}
