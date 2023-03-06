/* THREADS.C */

#include <lwp/lwp.h>
#include <lwp/stackdep.h>
#include "debug.h"
#include "list.h"
#include "maxprio.h"
#include "sched.h"
#include "threads.h"
#include "util.h"

#define SCHEDP 2
#define NUM_STACKS 5
#define STACK_BYTES 1000

thread_t sched_id;

void process1(void)
{
    register int i;
    extern LIST *process_list;
    TID myid;


    myid = t_myid();

    aprintf("process1 - process[%d] entered\n", myid);
    for (i = 1; i <= 100; i++)
	aprintf("process1 - process[%d] - i = %d\n", myid, i);
    t_destroy();
    aprintf("process1 - process[%d] exiting\n", myid);
}

void process2(void)
{
    register int i;
    TID myid;

    myid = t_myid();

    aprintf("process2 - process[%d] entered\n", myid);
    for (i = 1; i <= 100; i++)
	aprintf("process2 - process[%d] - i = %d\n", myid, i);
    t_destroy();
    aprintf("process2 - process[%d] exiting\n", myid);
}

void process3(void)
{
    register int i;
    TID myid;


    myid = t_myid();

    aprintf("process3 - process[%d] entered\n", myid);
    for (i = 1; i <= 100; i++)
	aprintf("process3 - process[%d] - i = %d\n", myid, i);
    t_destroy();
    aprintf("process3 - process[%d] exiting\n", myid);
}

void process4(void)
{
    register int i;
    TID myid;

    myid = t_myid();

    aprintf("process4 - process[%d] entered\n", myid);
    t_block();
    for (i = 1; i <= 100; i++)
	aprintf("process4 - process[%d] - i = %d\n", myid, i);
    t_destroy();
    aprintf("process4 - process[%d] exiting\n", myid);
}

void start_procs(int argc, char *argv[])
{
    register int i;
    char parameter;

    for (i = 1; i < argc; i++)
    {
	switch (*argv[i])
	{
	case 'A':
	    if ((t_ready(t_create(process1))) == -1)
	    {
		aprintf("start_procs - error creating process1 - halting\n");
		pod_exit(1);
	    }
	    else
		debug("start_procs - process1 created");
	    break;
	case 'B':
	    if
	      ((t_ready(t_create(process2))) == -1)
	    {
		aprintf("start_procs - error creating process2 - halting\n");
		pod_exit(1);
	    }
	    else
		debug(" start_procs - process2 created ");
	    break;
	case 'C':
	    if ((t_ready(t_create(process3))) == -1)
	    {
		aprintf("start_procs - error creating process3 - halting\n");
		pod_exit(1);
	    }
	    else
		debug("start_procs - process3 created");
	    break;
	case 'D':
	    if
	      ((t_ready(t_create(process4))) == -1)
	    {
		aprintf("start_procs - error creating process4 - halting\n");
		pod_exit(1);
	    }
	    else
		debug(" start_procs - process4 created ");
	    break;
	case 'E':
	    if ((t_ready(t_create(tg1))) == -1)
	    {
		aprintf("start_procs - error creating tg1 - halting\n");
		pod_exit(1);
	    }
	    else
		debug(" start_procs - tg1 created ");
	    break;
	case 'F':
	    if ((t_ready(t_create(tg2))) == -1)
	    {
		aprintf("start_procs - error creating tg2 - halting\n");
		pod_exit(1);
	    }
	    else
		debug("start_procs - tg2 created");
	    break;
	case 'G':
	    if
	      ((t_ready(t_create(tg3))) == -1)
	    {
		aprintf("start_procs - error creating tg3 - halting\n");
		pod_exit(1);
	    }
	    else
		debug(" start_procs - tg3 created ");
	    break;
	default:
	    aprintf("start_procs(default) - error creating [%s] - halting\n", argv[i]);
	}
    }
}
