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
    char buf[256];
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

char *itoa(int num, char *str)
/*-----------------------------------------------------------------------------+
|  itoa: converts 'num' to ascii string, places it in 'str' and returns a      |
|  pointer to 'str'.  NOTE:  The size of 'num' is very system dependent. i.e.  |
|  how large the system 'word' is. passing itoa numbers that exceed system     |
|  capabilities will result in erronious results.                              |
+-----------------------------------------------------------------------------*/
{
    register int i = 0, j, temp;
    while (num > 0)
    {
	str[i++] = (num % 10) + '0';
	num /= 10;
    }
    str[i] = '\0';
    for (j = 0, i--; i > j; j++, i--)
    {
	temp = str[i];
	str[i] = str[j];
	str[j] = temp;
    }
    return (str);
}
