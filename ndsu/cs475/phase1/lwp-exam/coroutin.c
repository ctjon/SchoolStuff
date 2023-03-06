/*
 * File: coroutines.c
 *
 * Example of coroutines running under the Lighweight Process library on
 * the Solbourne.  Prints the numbers 1 through 7 while switching between
 * threads.
 *
 * To compile this, type the following at the Unix prompt:
 *	gcc -o coroutines coroutines.c -llwp
 *
 * 90Feb22 BCP Created from the Solbourne manual, page 6-5.
 * 93Jan25 DMR Converted to Standard C.
 */

#include <stdio.h>
#include <lwp/lwp.h>
#include <lwp/stackdep.h>

thread_t co1;		/* main's tid */
thread_t co2;		/* coroutine's tid */
thread_t co3;		/* other's tid */


int coroutine( void );
int other( void );


int
main( int argc, char **argv ){

	/*
	 * Get information on main thread.  Side effect is the initialization
	 *  of the lwp library, and the change of main() into a thread.
	 */
	lwp_self(&co1);

	/*
	 * Initialize the stack cache to have 3 1000 byte stacks.
	 */
	lwp_setstkcache(1000, 3);

	/*
	 * Create the two other coroutines.
	 */
	lwp_create(&co2, coroutine, MINPRIO, 0, lwp_newstk(), 0);
	lwp_create(&co3, other, MINPRIO, 0, lwp_newstk(), 0);

	/*
	 * Print a 1, then yield execution.  Next thread to run will be
	 *  coroutine().
	 */
	printf("1\n");
	lwp_yield(THREADNULL);
	printf("4\n");

	/*
	 * Explicit yield to co3, other().
	 */
	lwp_yield(co3);
	printf("6\n");
	exit(0);
}


int coroutine ()
{
	printf("2\n");
	/* Yield execution. */
	if (lwp_yield(THREADNULL) < 0)
	{	lwp_perror("bad yield");
		return;
	}
	printf("7\n");
}


int other ()
{
	printf("3\n");
	/* Yield execution. */
	lwp_yield(THREADNULL);
	printf("5\n");
}
