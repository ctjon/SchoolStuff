/*
 * File: simple.c
 *
 * Simple example which uses the Lightweight Process library on the Solbourne.
 *
 * To compile this example, type the following at the Unix prompt:
 *	gcc -o simple simple.c -llwp
 *
 * 90Feb22 BCP Created from Solbourne manual example, page 6-3.
 */

#include <lwp/lwp.h>
#include <lwp/stackdep.h>

#define MAXPRIO 10

int main (argc, argv)
	int argc;
	char *argv[];
{	thread_t tid;
	int task();

	printf("main here\n");
	/* Set pod maximum priority.  Has the side effect of initializing
	   the lwp library, and also changes main() into a thread having
	   priority MAXPRIO. */
	(void)pod_setmaxpri(MAXPRIO);
	/* Set up thread stack cache to have 2 stacks of 1000 bytes. */
	lwp_setstkcache(1000, 2);
	/* Create the thread at MAXPRIO using one of the stacks in the
	   stack cache. */
	lwp_create(&tid, task, MAXPRIO, 0, lwp_newstk(), 0);
	/* Fall through, terminating this thread.  task() will now run. */
}

int task ()
{
	printf("hello world\n");
	/* Fall through, terminating this thread. */
}
