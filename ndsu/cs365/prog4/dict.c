#include <stdio.h>
#include "tree.h"
#include "soundex.h"


TREE dictionary;

TREE *mis_spell (dictionary, output_file, word)
/*-----------------------------------------------------------------------------+
| requires - a character input string                                          |
| modifies - word                                                              |
| effects  - notifies user and corrects mispelled word                         |
+-----------------------------------------------------------------------------*/
TREE *dictionary;
FILE *output_file;
char *word;

{
	int ret, valid_option;
	char option[80], temp[80];

	valid_option = FALSE;

	while (!valid_option)
	  {
		  printf ("\n%s [%s]\n", "Mispelled/Unknown word->", word);
		  printf ("%s\n", "Enter \"n\" for no change without adding to dictionary");
		  printf ("%s\n", "\"s\" for a suggestion");
		  printf ("%s\n\n", "or \"a\" to leave unchanged and add to dictionary");

		  scanf ("%s", option);

		  switch (option[0])
		    {
		    case 'n':
			    valid_option = TRUE;
			    break;
		    case 's':
			    printf ("\nsuggestions\n");
			    strcpy (temp, soundex_rep_of (word));
			    searching_traverse (dictionary, temp);
			    printf ("\nPlease Enter New Word -> ");
			    scanf ("%s", word);
			    fprintf (output_file, "%s ", word);
			    valid_option = TRUE;
			    break;
		    case 'a':
			    dictionary = add_avl_node (dictionary, &ret, word);
			    fprintf (output_file, "%s ", word);
			    valid_option = TRUE;
			    break;
		    default:

			    printf ("%s %s\n", "Invalid Option", option);
			    break;
		    }
	  }
	return (dictionary);
}

TREE *load_dictionary (dict_name)
/*-----------------------------------------------------------------------------+
| requires - nothing                                                           |
| modifies - dictionary                                                        |
| effects  - initializes and loads the dictionary                              |
+-----------------------------------------------------------------------------*/
char *dict_name;

{
	FILE *dict_file;
	TREE *dictionary;
	char tmp[80];
	int ret;

	dictionary = create_tree ();

	if ((dict_file = fopen (dict_name, "r")) == NULL)
	  {
		  perror ("can't open dictionary ", dict_name);
		  exit (1);
	  }
	else
	  {

		  while (!feof (dict_file))
		    {
			    if (get_next_word (dict_file, tmp) == FALSE)
				    break;
			    dictionary = add_avl_node (dictionary, &ret, tmp);
		    }
		  fclose (dict_file);
		  return dictionary;
	  }
}


void save_dictionary (dictionary, dict_name)
/*-----------------------------------------------------------------------------+
| requires - dictionary is a valid tree                                        |
| modifies - dictionary                                                        |
| effects  - saves dictionary to disk in dict_name                             |
+-----------------------------------------------------------------------------*/
TREE *dictionary;
char *dict_name;

{

	FILE *dict_file;

	if ((dict_file = fopen (dict_name, "w")) == NULL)
	  {
		  perror ("can't save dictionary");
		  exit (1);
	  }
	else
	  {
		  save_tree (dict_file, dictionary);
		  fclose (dict_file);
	  }
}
