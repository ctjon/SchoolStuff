/* $RCSfile: tg2.c,v $$Revision: 1.4 $$Date: 1993/02/07 04:28:06 $ */


#include "tg2private.h"
#include <lwp/lwp.h>
#include "tg.h"
#include "sem.h"
#include "sched.h"
/*
#include "semaphore.h"
#include "thread.h"
*/


static char buffer[SIZ_BUFFER];	/* should be at least MAX_LOOP*SIZ_ALPHABET */
static char alphabet[] = "abcdefghijklmnopqrstuvwxyz";


int tg2 ()
{	int tid;
	int i;


	s_create(NAM_BOUND, COUNT_BOUND);

	tid = t_create(consumer);
	t_ready( tid );
	tid = t_create(producer);
	t_ready( tid );

	s_create(NAM_SHARE, COUNT_SHARE);
	for (i = 0; i < MAX_SHARE; i++)
	{	aprintf("tg2: creating and readying Group 2 thread %d\n",
			i+1);
		tid = t_create(share);
		t_ready(tid);
	}
	aprintf( "tg2: done, destroying self\n");
	t_destroy();
}

/*
 * Producer thread.  Produces letters which ranges from A to Z MAX_LOOP times,
 * in order, then dies.  Signals the consumer after the production of each
 * letter.
 */
static int producer ()
{	thread_t tid;
	char ch;
	int i, j, b = 0;
	SID p;


	p = s_open(NAM_BOUND);

	for (i = 0; i < MAX_LOOP; i++)
	{	for (j = 0; j < SIZ_ALPHABET; j++)
		{	ch = alphabet[j];
			buffer[b] = ch;
			if (++b >= SIZ_BUFFER) b = 0;
			aprintf( "producer: produced %c\n", ch);
			s_signal(p);
		}
	}
	aprintf( "producer: all done\n");
	s_close(p);
	t_destroy();
}

/*
 * Consumer thread.  Consumes the letters produced by producer(), printing
 * them on stdout.
 */
static int consumer ()
{	thread_t tid;
	char ch;
	int b = 0;
	SID c;

	if (lwp_self(&tid) == -1)
	{	aprintf( "consumer: couldn't identify self, aborting\n");
		return;
	}
	aprintf( "consumer: identifying self thread_t=%d\n", tid);
	aprintf( "consumer: opening semaphore\n");
	c = s_open(NAM_BOUND);
	aprintf( "consumer: beginning to empty buffer\n");
	while (1)
	{	s_wait(c);
		ch = buffer[b];
		if (++b >= SIZ_BUFFER) b = 0;
		aprintf( "consumer: got character %c\n", ch);
	}
	s_close(c);	/* NOTREACHED */
	t_destroy();	/* NOTREACHED */
}

/*
 * Share thread.  Shares a hypothetical resource.
 */
static int share ()
{	thread_t tid;
	int i, j;
	SID s;

	if (lwp_self(&tid) == -1)
	{	aprintf( "G2 thread: couldn't identify self, aborting\n");
		exit(2);
	}
	aprintf( "G2 thread: identifying self thread_t=%d\n", tid);
	aprintf( "G2 thread_t=%d opening semaphore\n", tid);
	s = s_open(NAM_SHARE);
	for (i = 0; i < MAX_LOOP; i++)
	{	aprintf( "G2 thread_t=%d: attempting to enter critical section\n", tid);
		s_wait(s);
		aprintf( "G2 thread_t=%d: in critical section\n", tid);
		for (j = 0; j < MAX_IDLE; j++);
		aprintf( "G2 thread_t=%d: exiting critical section\n", tid);
		s_signal(s);
		aprintf( "G2 thread_t=%d out of critical section\n", tid);
	}
	aprintf( "G2 thread_t=%d all done\n", tid);
	s_close(s);
	t_destroy();
}
