/* $RCSfile: tg1.c,v $$Revision: 1.4 $$Date: 1993/02/07 04:28:06 $ */

/*
 * CS475 - Operating System Design
 *
 * File: tg1.c
 * Author: Blayne Puklich
 * Creation date: Wed Mar 21 01:22:57 CST 1990
 *
 * Description
 *	Source file for tg1.
 *
 * History:
 * 90Apr14 BCP Added idle loop in looper() and blocker().
 * 90Apr30 BCP Changed to use the function my_printf() for I/O.
 * 93Feb6  DMR cosmetic changes, including use of aprintf rather than
 *		my_printf.
 */

#include "tg.h"
#include "tg1private.h"
#include <lwp/lwp.h>
#include "sched.h"

/*
 * Test Group 1 main thread.
 */
int tg1 ()
{	int i;
	TID loopers[MAX_LOOPER];
	TID tid;

	/* create the Group 1 looper() threads */
	for (i = 0; i < MAX_LOOPER; i++)
	{	aprintf( "tg1: creating Group 1 thread %d\n", i+1);
		loopers[i] = t_create(looper);
		aprintf( "tg1: Group 1 thread created, TId=%d\n",
			loopers[i]);
	}
	/* ready the Group 1 looper() threads */
	for (i = 0; i < MAX_LOOPER; i++)
	{	aprintf( "tg1: readying Group 1 thread TId=%d\n",
			loopers[i]);
		t_ready(loopers[i]);
		aprintf("tg1: Group 1 thread TId=%d ready\n", loopers[i]);
	}
	/* create the Group 2 blocker() threads */
	for (i = 0; i < MAX_BLOCKER; i++)
	{	aprintf( "tg1: creating Group 2 thread %d\n", i+1);
		tid = t_create(blocker);
		aprintf( "tg1: Group 2 thread created, TId=%d\n", tid);
		aprintf( "tg1: readying Group 2 thread TId=%d\n", tid);
		t_ready(tid);
		aprintf( "tg1: Group 2 thread TId=%d readied\n", tid);
	}
	t_destroy();
}

/*
 * Looper thread which identifies itself at invokation and each time through
 * the loop.
 */
static int looper ()
{	thread_t tid;
	int i, j;

	if (lwp_self(&tid) == -1)
	{	aprintf( "Group 1 thread attempt to identify self failed!\n");
		return;
	}
	aprintf( "Group 1 thread thread_t=%d identifying\n", tid);
	for (i = 0; i < MAX_LOOP; i++)
	{	aprintf("Group 1 thread thread_t=%d loop pass %d\n", tid, i+1);
		for (j = 0; j < MAX_IDLE; j++);
	}
	t_destroy();
}

/*
 * Blocker thread which identifies itself at invokation and blocks itself.
 */
static int blocker ()
{	thread_t tid;
	int i, j;

	if (lwp_self(&tid) == -1)
	{	aprintf( "Group 2 thread attempt to identify self failed!\n");
		return;
	}
	aprintf( "Group 2 thread thread_t=%d identifying\n", tid);
	aprintf( "Group 2 thread thread_t=%d blocking\n", tid);
	t_block();
	/* should not get this far */
	for (i = 0; i < MAX_LOOP; i++)
	{	aprintf( "Group 2 thread thread_t=%d loop pass %d\n",
			tid, i+1);
		for (j = 0; j < MAX_IDLE; j++);
	}
	t_destroy();
}
