/* UTIL.H */

#ifndef __UTILH__
#define __UTILH__

#ifdef __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

#include <stdio.h>

#ifdef DEBUG
#ifdef __STDC__
void debug(char *fmt,...);
#else
void debug(void);
#endif

/*----------------------------------------------------------------------------+
| REQUIRES: a valid character string as input                                 |
| MODIFIES: nothing                                                           |
| EFFECTS:  prints a variable error message to the screen                     |
+----------------------------------------------------------------------------*/
#else
#define debug
#endif

#endif				/* __UTILH__ */

char *itoa(int num, char *str);
/*-----------------------------------------------------------------------------+
|  itoa: converts 'num' to ascii string, places it in 'str' and returns a      |
|  pointer to 'str'.  NOTE:  The size of 'num' is very system dependent. i.e.  |
|  how large the system 'word' is. passing itoa numbers that exceed system     |
|  capabilities will result in erronious results.                              |
+-----------------------------------------------------------------------------*/
