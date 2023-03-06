/* UTIL.C */

#include "aprintf.h"
#define DEBUG
#include "util.h"

#ifdef __STDC__
void debug(char *fmt,...)
/*----------------------------------------------------------------------------+
| REQUIRES: a valid character string as input                                 |
| MODIFIES: nothing                                                           |
| EFFECTS:  prints a variable error message to the screen                     |
+----------------------------------------------------------------------------*/
#else
void debug(va_alist)
va_dcl
#endif
{
    va_list ap;
    int arg;
    char buf[80];
#ifndef __STDC__
    char *fmt;
    va_start(ap);
    fmt = va_arg(ap, char *);
#else
    va_start(ap, fmt);
#endif

    vsprintf(buf, fmt, ap);
    aprintf("%s\n", buf);
    va_end(ap);
}
