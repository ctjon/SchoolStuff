/* $RCSfile: tg3private.h,v $$Revision: 1.2 $$Date: 1993/02/07 04:28:06 $ */

/*
 * CS475 - Operating System Design
 *
 * File: tg3private.h
 * Author: Blayne Puklich
 * Creation date: Fri Mar 23 13:57:07 CST 1990
 *
 * Description
 *	Header file for tg3private.
 *
 * History:
 */

#ifndef __tg3private__
#define __tg3private__

/* resource sharing stuff */
#define NAM_MUTEX 100
#define COUNT_MUTEX 1
#define MAX_SHARE 10
#define MAX_LOOP 10
#define MAX_GET 5

#define MAX_STRING 256

/* function declarations */

static int share();

#endif
