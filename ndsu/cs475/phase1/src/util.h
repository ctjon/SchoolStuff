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
