/* THREADS.C */

#include <lwp/lwp.h>
#include <lwp/stackdep.h>
#include <sys/fcntl.h>
#include "aprintf.h"
#include "debug.h"
#include "fs.h"
#include "list.h"
#include "master.h"
#include "maxprio.h"
#include "mem.h"
#include "sched.h"
#include "threads.h"
#include "util.h"

#define SCHEDP 2
#define NUM_STACKS 5
#define STACK_BYTES 1000

#ifdef DEBUG
#include <stdio.h>
#endif

#define MAX_FS_PROCS 10

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
    aprintf("process1 - process[%d] exiting\n", myid);
    t_destroy();
}

void process2(void)
{
    register int i;
    TID myid;

    myid = t_myid();

    aprintf("process2 - process[%d] entered\n", myid);
    for (i = 1; i <= 100; i++)
	aprintf("process2 - process[%d] - i = %d\n", myid, i);
    aprintf("process2 - process[%d] exiting\n", myid);
    t_destroy();
}

void process3(void)
{
    register int i;
    TID myid;


    myid = t_myid();

    aprintf("process3 - process[%d] entered\n", myid);
    for (i = 1; i <= 100; i++)
	aprintf("process3 - process[%d] - i = %d\n", myid, i);
    aprintf("process3 - process[%d] exiting\n", myid);
    t_destroy();
}

void process4(void)
{
    register int i;
    TID myid;

    myid = t_myid();

    aprintf("process4 - process[%d] entered\n", myid);
    for (i = 1; i <= 100; i++)
	aprintf("process4 - process[%d] - i = %d\n", myid, i);
    aprintf("process4 - process[%d] exiting\n", myid);
    t_destroy();
}

void ipc_test1(void)
{
    register int i;
    TID myid;
    TID ptid;
    BUFFER *buf1, *buf2;

    myid = t_myid();
    aprintf("ipc_test1 - process[%d] entered\n", myid);

    ipc_stat();
    debug("ipc_test1 - running");

    buf1 = b_get();
    debug("ipc_test1 - running");
    sprintf((char *) buf1, "%-64s", "from 1 - i am fine 2");
    debug("ipc_test1 - running");
    debug("ipc_test1 - sending \n[%s] to [TID%d]", buf1, myid + 1);
    debug("ipc_test1 - running");
    m_send(myid + 1, buf1);
    debug("ipc_test1 - running");
    b_release(buf1);
    debug("ipc_test1 - running");

    ipc_stat();
    debug("ipc_test1 - running");

    buf1 = b_get();
    debug("ipc_test1 - running");
    sprintf((char *) buf1, "%-64s", "from 1 - are you fine 3?");
    debug("ipc_test1 - running");
    debug("ipc_test1 - sending \n[%s] to [TID%d]", buf1, myid + 2);
    debug("ipc_test1 - running");
    m_send(myid + 2, buf1);
    debug("ipc_test1 - running");
    b_release(buf1);
    debug("ipc_test1 - running");

    ipc_stat();
    debug("ipc_test1 - running");


    debug("ipc_test1 - running");
    ipc_stat();
    debug("ipc_test1 - running");

    ipc_stat();
    debug("ipc_test1 - running");

    buf2 = b_get();
    debug("ipc_test1 - running");
    m_receive(&ptid, buf2);
    debug("ipc_test1 - running");
    debug("ipc_test1 - received \n[%s] from [TID%d]", buf2, ptid);
    debug("ipc_test1 - running");
    b_release(buf2);
    debug("ipc_test1 - running");

    ipc_stat();
    debug("ipc_test1 - running");

    buf2 = b_get();
    debug("ipc_test1 - running");
    m_receive(&ptid, buf2);
    debug("ipc_test1 - running");
    debug("ipc_test1 - received \n[%s] from [TID%d]", buf2, ptid);
    debug("ipc_test1 - running");
    b_release(buf2);
    debug("ipc_test1 - running");

    ipc_stat();
    debug("ipc_test1 - running");

    buf2 = b_get();
    debug("ipc_test1 - running");
    m_receive(&ptid, buf2);
    debug("ipc_test1 - running");
    debug("ipc_test1 - received \n[%s] from [TID%d]", buf2, ptid);
    debug("ipc_test1 - running");
    b_release(buf2);
    debug("ipc_test1 - running");

    ipc_stat();
    debug("ipc_test1 - running");

    buf2 = b_get();
    debug("ipc_test1 - running");
    m_receive(&ptid, buf2);
    debug("ipc_test1 - running");
    debug("ipc_test1 - received \n[%s] from [TID%d]", buf2, ptid);
    debug("ipc_test1 - running");
    b_release(buf2);
    debug("ipc_test1 - running");

    ipc_stat();
    debug("ipc_test1 - running");

    buf1 = b_get();
    debug("ipc_test1 - running");
    sprintf((char *) buf1, "%-64s", "from 1 - hello 2");
    debug("ipc_test1 - running");
    debug("ipc_test1 - sending \n[%s] to [TID%d]", buf1, myid + 1);
    debug("ipc_test1 - running");
    m_send(myid + 1, buf1);
    debug("ipc_test1 - running");
    b_release(buf1);
    debug("ipc_test1 - running");

    ipc_stat();
    debug("ipc_test1 - running");

    buf1 = b_get();
    debug("ipc_test1 - running");
    sprintf((char *) buf1, "%-64s", "from 1 - how are you 3");
    debug("ipc_test1 - running");
    debug("ipc_test1 - sending \n[%s] to [TID%d]", buf1, myid + 2);
    debug("ipc_test1 - running");
    m_send(myid + 2, buf1);
    debug("ipc_test1 - running");
    b_release(buf1);
    debug("ipc_test1 - running");


    aprintf("ipc_test1 - process[%d] exiting\n", myid);
    t_destroy();
}

void ipc_test2(void)
{
    register int i;
    TID myid;
    TID ptid;
    BUFFER *buf1, *buf2;

    myid = t_myid();
    aprintf("ipc_test2 - process[%d] entered\n", myid);


    debug("ipc_test2 - running");
    ipc_stat();
    debug("ipc_test2 - running");

    buf1 = b_get();
    debug("ipc_test2 - running");
    sprintf((char *) buf1, "%-64s", "from 2 - goodbye 1");
    debug("ipc_test2 - running");
    debug("ipc_test2 - sending \n[%s] to [TID%d]", buf1, myid - 1);
    debug("ipc_test2 - running");
    m_send(myid - 1, buf1);
    debug("ipc_test2 - running");
    b_release(buf1);
    debug("ipc_test2 - running");

    ipc_stat();
    debug("ipc_test2 - running");

    buf1 = b_get();
    debug("ipc_test2 - running");
    sprintf((char *) buf1, "%-64s", "from 2 - piss off 3");
    debug("ipc_test2 - running");
    debug("ipc_test2 - sending \n[%s] to [TID%d]", buf1, myid + 1);
    debug("ipc_test2 - running");
    m_send(myid + 1, buf1);
    debug("ipc_test2 - running");
    b_release(buf1);
    debug("ipc_test2 - running");

    ipc_stat();
    debug("ipc_test2 - running");

    buf1 = b_get();
    debug("ipc_test2 - running");
    sprintf((char *) buf1, "%-64s", "from 2 - take a hike 1");
    debug("ipc_test2 - running");
    debug("ipc_test2 - sending \n[%s] to [TID%d]", buf1, myid - 1);
    debug("ipc_test2 - running");
    m_send(myid - 1, buf1);
    debug("ipc_test2 - running");
    b_release(buf1);
    debug("ipc_test2 - running");

    ipc_stat();
    debug("ipc_test2 - running");

    buf1 = b_get();
    debug("ipc_test2 - running");
    sprintf((char *) buf1, "%-64s", "from 2 - hey 3, who cares?");
    debug("ipc_test2 - running");
    debug("ipc_test2 - sending \n[%s] to [TID%d]", buf1, myid + 1);
    debug("ipc_test2 - running");
    m_send(myid + 1, buf1);
    debug("ipc_test2 - running");
    b_release(buf1);
    debug("ipc_test2 - running");

    ipc_stat();
    debug("ipc_test2 - running");

    buf2 = b_get();
    debug("ipc_test2 - running");
    m_receive(&ptid, buf2);
    debug("ipc_test2 - running");
    debug("ipc_test2 - received \n[%s] from [TID%d]", buf2, ptid);
    debug("ipc_test2 - running");
    b_release(buf2);
    debug("ipc_test2 - running");

    ipc_stat();
    debug("ipc_test2 - running");

    buf2 = b_get();
    debug("ipc_test2 - running");
    m_receive(&ptid, buf2);
    debug("ipc_test2 - running");
    debug("ipc_test2 - received \n[%s] from [TID%d]", buf2, ptid);
    debug("ipc_test2 - running");
    b_release(buf2);
    debug("ipc_test2 - running");

    ipc_stat();
    debug("ipc_test2 - running");

    buf2 = b_get();
    debug("ipc_test2 - running");
    m_receive(&ptid, buf2);
    debug("ipc_test2 - running");
    debug("ipc_test2 - received \n[%s] from [TID%d]", buf2, ptid);
    debug("ipc_test2 - running");
    b_release(buf2);
    debug("ipc_test2 - running");

    ipc_stat();
    debug("ipc_test2 - running");

    buf2 = b_get();
    debug("ipc_test2 - running");
    m_receive(&ptid, buf2);
    debug("ipc_test2 - running");
    debug("ipc_test2 - received \n[%s] from [TID%d]", buf2, ptid);
    debug("ipc_test2 - running");
    b_release(buf2);
    debug("ipc_test2 - running");

    ipc_stat();
    debug("ipc_test2 - running");

    aprintf("ipc_test2 - process[%d] exiting\n", myid);
    t_destroy();
}

void ipc_test3(void)
{
    register int i;
    TID myid;
    TID ptid;
    BUFFER *buf1, *buf2;

    myid = t_myid();
    aprintf("ipc_test3 - process[%d] entered\n", myid);


    ipc_stat();
    debug("ipc_test3 - running");

    buf1 = b_get();
    debug("ipc_test3 - running");
    sprintf((char *) buf1, "%-64s", "from 3 - hello 1");
    debug("ipc_test3 - running");
    debug("ipc_test3 - sending \n[%s] to [TID%d]", buf1, myid - 2);
    debug("ipc_test3 - running");
    m_send(myid - 2, buf1);
    debug("ipc_test3 - running");
    b_release(buf1);
    debug("ipc_test3 - running");

    ipc_stat();
    debug("ipc_test3 - running");

    buf1 = b_get();
    debug("ipc_test3 - running");
    sprintf((char *) buf1, "%-64s", "from 3 - hello 2");
    debug("ipc_test3 - running");
    debug("ipc_test3 - sending \n[%s] to [TID%d]", buf1, myid - 1);
    debug("ipc_test3 - running");
    m_send(myid - 1, buf1);
    debug("ipc_test3 - running");
    b_release(buf1);
    debug("ipc_test3 - running");

    ipc_stat();
    debug("ipc_test3 - running");

    buf1 = b_get();
    debug("ipc_test3 - running");
    sprintf((char *) buf1, "%-64s", "from 3 - i am fine 1");
    debug("ipc_test3 - running");
    debug("ipc_test3 - sending \n[%s] to [TID%d]", buf1, myid - 2);
    debug("ipc_test3 - running");
    m_send(myid - 2, buf1);
    debug("ipc_test3 - running");
    b_release(buf1);
    debug("ipc_test3 - running");

    ipc_stat();
    debug("ipc_test3 - running");

    buf1 = b_get();
    debug("ipc_test3 - running");
    sprintf((char *) buf1, "%-64s", "from 3 - i am fine 2?");
    debug("ipc_test3 - running");
    debug("ipc_test3 - sending \n[%s] to [TID%d]", buf1, myid - 1);
    debug("ipc_test3 - running");
    m_send(myid - 1, buf1);
    debug("ipc_test3 - running");
    b_release(buf1);
    debug("ipc_test3 - running");

    ipc_stat();
    debug("ipc_test3 - running");

    buf2 = b_get();
    debug("ipc_test3 - running");
    m_receive(&ptid, buf2);
    debug("ipc_test3 - running");
    debug("ipc_test3 - received \n[%s] from [TID%d]", buf2, ptid);
    debug("ipc_test3 - running");
    b_release(buf2);
    debug("ipc_test3 - running");

    ipc_stat();
    debug("ipc_test3 - running");

    buf2 = b_get();
    debug("ipc_test3 - running");
    m_receive(&ptid, buf2);
    debug("ipc_test3 - running");
    debug("ipc_test3 - received \n[%s] from [TID%d]", buf2, ptid);
    debug("ipc_test3 - running");
    b_release(buf2);
    debug("ipc_test3 - running");

    debug("ipc_test3 - running");
    ipc_stat();
    debug("ipc_test3 - running");

    buf2 = b_get();
    debug("ipc_test3 - running");
    m_receive(&ptid, buf2);
    debug("ipc_test3 - running");
    debug("ipc_test3 - received \n[%s] from [TID%d]", buf2, ptid);
    debug("ipc_test3 - running");
    b_release(buf2);
    debug("ipc_test3 - running");

    ipc_stat();
    debug("ipc_test3 - running");

    buf2 = b_get();
    debug("ipc_test3 - running");
    m_receive(&ptid, buf2);
    debug("ipc_test3 - running");
    debug("ipc_test3 - received \n[%s] from [TID%d]", buf2, ptid);
    debug("ipc_test3 - running");
    b_release(buf2);
    debug("ipc_test3 - running");

    ipc_stat();
    debug("ipc_test3 - running");

    aprintf("ipc_test3 - process[%d] exiting\n", myid);
    t_destroy();
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
	case 'H':
	    if
	      ((t_ready(t_create(ipc_test1))) == -1)
	    {
		aprintf("start_procs - error creating ipc_test1 - halting\n");
		pod_exit(1);
	    }
	    else
		debug(" start_procs - ipc_test1 initiated ");
	    if
	      ((t_ready(t_create(ipc_test2))) == -1)
	    {
		aprintf("start_procs - error creating ipc_test2 - halting\n");
		pod_exit(1);
	    }
	    else
		debug(" start_procs - ipc_test2 initiated ");
	    if
	      ((t_ready(t_create(ipc_test3))) == -1)
	    {
		aprintf("start_procs - error creating ipc_test3 - halting\n");
		pod_exit(1);
	    }
	    else
		debug(" start_procs - ipc_test3 initiated ");
	    break;
	case 'I':
	    if
	      ((t_ready(t_create(master_thread))) == -1)
	    {
		aprintf("start_procs - error creating master_thread - halting\n");
		pod_exit(1);
	    }
	    else
		debug(" start_procs - master_thread initiated ");
	    break;
	default:
	    aprintf("start_procs(default) - error creating [%s] - halting\n", argv[i]);
	}
    }
}
