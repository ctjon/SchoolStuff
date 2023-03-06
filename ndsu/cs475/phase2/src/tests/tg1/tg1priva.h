/* $RCSfile: tg1private.h,v $$Revision: 1.4 $$Date: 1993/02/07 04:28:06 $ */

/*
 * CS475 - Operating System Design
 *
 * File: tg1private.h
 * Author: Blayne Puklich
 * Creation date: Fri Mar 23 13:48:37 CST 1990
 *
 * Description
 *	Header file for tg1private.
 *
 * History:
 * 90Apr14 BCP Added MAX_IDLE.
 * 93Feb6  DMR removed my_printf
 */

#ifndef __tg1private__
#define __tg1private__

#define MAX_LOOPER 10
#define MAX_BLOCKER 10
#define MAX_LOOP 20
#define MAX_IDLE 1000

#define MAX_STRING 256

/* function declarations */

static int looper ( void );
static int blocker ( void );


#endif
