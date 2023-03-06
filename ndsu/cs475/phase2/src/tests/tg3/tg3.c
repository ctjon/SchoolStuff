/* $RCSfile: tg3.c,v $$Revision: 1.2 $$Date: 1993/02/07 04:28:06 $ */

/*
 * CS475 - Operating System Design
 *
 * File: tg3.c
 * Author: Blayne Puklich
 * Creation date: Fri Mar 23 13:57:02 CST 1990
 *
 * Description
 *	Source file for tg3.
 *
 * History:
 * 90Apr30 BCP Changed to use my_printf().
 */

#include "tg.h"
#include "tg3private.h"
#include <lwp/lwp.h>
#include "sched.h"
#include "sem.h"
#include "mem.h"

/* buffer allocation count (shared) */
static int bufCount = 0;

/*
 * Main thread for thread group 3.
 */
int tg3 ()
{	int i;
	TID tid;

	aprintf("tg3: creating mutual exclusion semaphore\n");
	s_create(NAM_MUTEX, COUNT_MUTEX);
	aprintf( "tg3: creating G1 threads\n");
	for (i = 0; i < MAX_SHARE; i++)
	{	aprintf( "tg3: creating G1 thread %d\n", i+1);
		tid = t_create(share);
		aprintf( "tg3: created G1 thread tid=%d\n", tid);
		aprintf( "tg3: readying G1 thread tid=%d\n", tid);
		t_ready(tid);
		aprintf( "tg3: G1 thread tid=%d ready\n", tid);
	}
	aprintf( "tg3: all done\n");
	t_destroy();
}

/*
 * Resource sharing thread.  Allocates MAX_GET buffers, then releases them.
 * Does this MAX_LOOP times.
 */
static int share ()
{	thread_t tid;
	Buffer bufs[MAX_GET];
	int i, bi;
	SID m;

	if (lwp_self(&tid) == -1)
	{	aprintf( "G1 thread couldn't identify self, aborting\n");
		return;
	}
	aprintf( "G1 thread: identifying self thread_t=%d\n", tid);
	aprintf( "G1 thread_t=%d opening semaphore\n", tid);
	m = s_open(NAM_MUTEX);
	for (i = 0; i < MAX_LOOP; i++)
	{	aprintf( "G1 thread_t=%d getting buffers\n", tid);
		for (bi = 0; bi < MAX_GET; bi++)
		{	bufs[bi] = b_get();
			s_wait(m);
			bufCount++;
			aprintf( "G1 thread_t=%d got buffer %d, count=%d\n",
			       tid, bufs[bi], bufCount);
			s_signal(m);
		}
		aprintf( "G1 thread_t=%d releasing buffers\n", tid);
		for (bi = 0; bi < MAX_GET; bi++)
		{	b_release(bufs[bi]);
			s_wait(m);
			bufCount--;
			aprintf( "G1 thread_t=%d released buffer %d, count=%d\n",
			       tid, bufs[bi], bufCount);
			s_signal(m);
		}
	}
	s_close(m);
	aprintf( "G1 thread_t=%d done\n", tid);
	t_destroy();
}
