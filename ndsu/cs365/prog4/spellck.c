#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include "dict.h"
#include "tree.h"
#include "soundex.h"
#include "copyfile.h"

#define DICTIONARY "dict.dat"


int get_next_word (input_file, buf)
/*-----------------------------------------------------------------------------+
| requires - input_file has been properly opened                               |
| modifies - nothing                                                           |
| effects  - sets buf equal to the next word from the stream input_file        |
+-----------------------------------------------------------------------------*/
FILE *input_file;
char *buf;

{
	char ch;
	register int i = 0;

	while (isspace (ch = fgetc (input_file)) && (!feof (input_file)));

	while ((ch != '\0') && (ch != EOF) && (!isspace (ch)))
	  {
		  buf[i++] = ch;
		  ch = fgetc (input_file);
	  }
	buf[i] = '\0';
	if (buf[0])
	  {
		  return TRUE;
	  }
	else
	  {
		  return FALSE;
	  }
}


TREE *process_file (dictionary, input_file, output_file)
/*-----------------------------------------------------------------------------+
| requires - *input_file and *output_file are defined                          |
| modifies - output_file                                                       |
| effects  - checks the spelling of the contents of input file and copies      |
|            input_file(with corrections) to output_file                       |
+-----------------------------------------------------------------------------*/
TREE *dictionary;
FILE *input_file, *output_file;

{
	char word[80];

	while (!feof (input_file))
	  {
		  if (get_next_word (input_file, word) == FALSE)
			  break;
		  if (is_in (dictionary, word))
		    {
			    fprintf (output_file, "%s ", word);
		    }
		  else
		    {
			    dictionary = mis_spell (dictionary, output_file, word);
		    }

	  }
	return (dictionary);
}

void Abort ()
{
	printf ("Bomb time\n");
	exit (1);
}

main (argc, argv)
/*----------------------------------------------------------------------------*/
int argc;
char *argv[];

{

	FILE *input_file, *temp_file;
	TREE *dictionary;

	signal (SIGSEGV, Abort);
	dictionary = load_dictionary (DICTIONARY);

	if (argc <= 1)
	  {
		  printf ("%s\n", "Usage: spellck <files...>");
		  exit (1);
	  }
	else
	  {
		  while (--argc > 0)
		    {
			    if ((input_file = fopen (*++argv, "r")) == NULL)
			      {
				      perror ("can't open ", *argv, " for input");
				      exit (1);
			      }
			    else if ((temp_file = tmpfile ())== NULL)
			      {
				      perror ("can't open ", *temp_file);
				      exit (1);
			      }
			    else
			      {
				      dictionary = process_file (dictionary,
						     input_file, temp_file);
				      fclose (input_file);
				      copy_file (temp_file, input_file);
				      fclose (temp_file);
			      }
		    }
	  }
	save_dictionary (dictionary, DICTIONARY);
	delete_tree (dictionary);
	exit (0);
}
