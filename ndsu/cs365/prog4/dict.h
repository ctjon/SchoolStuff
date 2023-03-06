#ifndef __DICTH__
#define __DICTH__
#include "tree.h"
#include "soundex.h"

TREE dictionary;

TREE *mis_spell ();

/*-----------------------------------------------------------------------------+
| requires - a character input string                                          |
| modifies - word                                                              |
| effects  - notifies user and corrects mispelled word, Updates dictionary     |
+-----------------------------------------------------------------------------*/


TREE *load_dictionary ();

/*-----------------------------------------------------------------------------+
| requires - nothing                                                           |
| modifies - dictionary                                                        |
| effects  - initializes and loads the dictionary                              |
+-----------------------------------------------------------------------------*/


void save_dictionary ();

/*-----------------------------------------------------------------------------+
| requires - dictionary is a valid tree                                        |
| modifies - dictionary                                                        |
| effects  - saves dictionary to disk in DICTONARY                             |
+-----------------------------------------------------------------------------*/

#endif				/* __DICTH__ */
