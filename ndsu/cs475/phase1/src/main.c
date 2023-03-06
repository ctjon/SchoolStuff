/* MAIN.C */

#include "debug.h"
#include "mem.h"
#include "sched.h"
#include "threads.h"
#include "util.h"

void main(int argc, char *argv[])
{
    thread_t main_id;

    if (argc < 2)
    {
	fprintf(stderr, "%s\n", "os4u - A|B|C|D|E|F|G where");
	fprintf(stderr, "%s\n", "       A = process1");
	fprintf(stderr, "%s\n", "       B = process2");
	fprintf(stderr, "%s\n", "       C = process3");
	fprintf(stderr, "%s\n", "       D = process4");
	fprintf(stderr, "%s\n", "       E = tg1");
	fprintf(stderr, "%s\n", "       F = tg2");
	fprintf(stderr, "%s\n", "       G = tg3");
	exit(1);		/* No Command Line args so quit */
    }
    (void) pod_setmaxpri(MAXPRIO);
    debug("main - main set to priority %d", MAXPRIO);

    lwp_self(&main_id);
    debug("main - main's ID = %d", main_id.thread_key);

    debug("main - mmallocing buffers");
    /* initializing the memory */
    mmalloc(MAXMEM);
    debug("main - mmalloc'ed buffers");

    debug("main - allocating stacks");
    lwp_setstkcache(STACK_BYTES, NUM_STACKS);
    debug("main - %d stacks allocated with %d bytes each", NUM_STACKS, STACK_BYTES);

    debug("main - creating scheduler");
    lwp_create(&sched_id, scheduler, SCHEDP, LWPSUSPEND, lwp_newstk(), 0);
    debug("main - scheduler created with tid = %d", sched_id.thread_key);
    debug("main - initiating t_init()");
    t_init();			/* Initializing the scheduler */
    debug("main - returned from t_init()");

    debug("main - starting process subsystems");
    start_procs(argc, argv);	/* call the thread groups */
    debug("main - process subsystems started ok");

    debug("main - yielding to scheduler");
    lwp_resume(sched_id);	/* giving scheduler control */
    exit(0);			/* exit main with no error condition */
}
