/* $RCSfile: tg2private.h,v $$Revision: 1.3 $$Date: 1993/02/07 04:28:06 $ */

/*
 * CS475 - Operating System Design
 *
 * File: tg2private.h
 * Author: Blayne Puklich
 * Creation date: Fri Mar 23 13:53:36 CST 1990
 *
 * Description
 *	Header file for tg2private.
 *
 * History:
 */

#ifndef __tg2private__
#define __tg2private__

/* maximum number of share threads */
#define MAX_SHARE 4

/* bounded buffer stuff */
#define NAM_BOUND 150
#define COUNT_BOUND 0
#define SIZ_BUFFER 256
#define SIZ_ALPHABET 26
#define MAX_LOOP 5

/* resource sharing stuff */
#define NAM_SHARE 200
#define COUNT_SHARE 1
#define MAX_SHARELOOP 20
#define MAX_IDLE 100

#define MAX_STRING 256

/* function declarations */

static int producer ( void );
static int consumer ( void );
static int share ( void );

#endif
