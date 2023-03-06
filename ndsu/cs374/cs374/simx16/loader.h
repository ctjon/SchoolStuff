#include     <stdio.h>

FILE *load_file ;

int load(char *load_file, unsigned int *off);
/* reads a *.xld file and loads the halfwords to memory */
/* returns -1 on failure and 0 on success */

