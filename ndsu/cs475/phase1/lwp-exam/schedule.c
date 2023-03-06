/*
 * Example of a simple round-robin scheduler using lightweight processes.
 * To stop this, type control-C.
 *
 * gcc -o scheduler scheduler.c -llwp
 *
 */

#include <stdio.h>
#include <lwp/lwp.h>
#include <lwp/stackdep.h>

int scheduler( void );
int task( int );


#define MAXPRIO 10

main( int argc, char **argv ){

	int i;

	pod_setmaxpri( MAXPRIO );
	lwp_setstkcache( 1000, 5 );
	lwp_create( (thread_t *)0, scheduler, MAXPRIO, 0, lwp_newstk(), 0 );
	for( i = 0; i < 3; i++ ){
		lwp_create( (thread_t *)0, task, MINPRIO, 0,
			   lwp_newstk(), 1, i );
	}
	exit(0);
}



int scheduler( void ){

	struct timeval quantum;

	quantum.tv_sec = 0;
	quantum.tv_usec = 10000;
	for(;;){
		lwp_sleep( &quantum );
		lwp_resched( MINPRIO );
	}

}



 /* these tasks are scheduled round-robin, preemptive */
 int task( int arg ){
	for(;;){
		printf("task %d\n", arg );
	}
}
