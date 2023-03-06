/* APRINTF.C */

#include <stdio.h>
#include <varargs.h>
#include "aprintf.h"
#include "crit.h"
#include "maxprio.h"

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif


int aprintf(va_alist)
va_dcl
{
    int old_priority;
    va_list args;
    int ret;
    char *fmt;
    char buf[1024];

    va_start(args);
    fmt = va_arg(args, char *);
    vsprintf(buf, fmt, args);
    va_end(args);

    /* enter critical section */
    old_priority = enter_crit();

    ret = printf("%s", buf);

    /* exit critical section */
    exit_crit(old_priority);
    return ret;
}
