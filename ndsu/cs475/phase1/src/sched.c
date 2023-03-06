/* SCHED.C */

#include "debug.h"
#include "maxprio.h"
#include "sched.h"
#include "sem.h"		/* include so that we can dump the sem list */
#include "util.h"

TID threadnum = 0;		/* incremented for each thread becomes id */
int num_created = 0;
int num_destroyed = 0;

TID t_create(void *f)
/*----------------------------------------------------------------------------+
| REQUIRES: t_init has been called once first                                 |
| MODIFIES: ready_q                                                           |
| EFFECTS: creates a thread, places it on ready_q and returns the id of thread|
|          returns 0 on success -1 on failure                                 |
+----------------------------------------------------------------------------*/
{
    thread_t new;
    THREAD proc_node;
    extern LIST *block_q;
    extern TID threadnum;
    extern int num_created;
    int old_priority;

    old_priority = enter_crit();
    debug("t_create - calling lwp_create");
    if (lwp_create(&new, f, 1, LWPSUSPEND, lwp_newstk(), 0) == 0)
    {
	/* new holds structure returned by lwp */

	/* setting up are thread structure */
	proc_node.id = ++threadnum;
	proc_node.thread = new;
	num_created++;		/* increment global number created */

	/* putting on blocked list */
	debug("t_create - adding thread[%d] to block_q", proc_node.id);
	block_q = insert_at_end(block_q, sizeof(THREAD), &proc_node);
	exit_crit(old_priority);
	return (proc_node.id);
    }
    else
    {
	aprintf("t_create - error calling lwp_create\n");
	exit_crit(old_priority);
	return (-1);
    }
}

int t_destroy(void)
/*----------------------------------------------------------------------------+
| REQUIRES: nothing                                                           |
| MODIFIES: calling thread and ready_q                                        |
| EFFECTS:  destroys the calling thread and returns 0 on success -1 on failure|
+----------------------------------------------------------------------------*/
{
    thread_t thread;
    extern int num_destroyed;

    num_destroyed++;
    debug("t_destroy - about to call lwp_destroy");
    return (lwp_destroy(SELF));
}


int t_block(void)
/*----------------------------------------------------------------------------+
| REQUIRES: nothing                                                           |
| MODIFIES: calling thread, ready_q, block_q                                  |
| EFFECTS: blocks the calling thread, removing it from ready_q and putting it |
|          on block_q, returns 1 on success 0 on failure                      |
+----------------------------------------------------------------------------*/
{
    extern LIST *ready_q;
    extern LIST *block_q;
    int old_prio;

    old_prio = enter_crit();

    debug("t_block - adding node to block_q");
    block_q = insert_at_end(block_q, sizeof(THREAD), ready_q->data);
    debug("t_block - deleting node from ready_q");
    ready_q = delete_node(ready_q);

    exit_crit(old_prio);

    debug("t_block - about to suspend the thread");
    return (lwp_suspend(SELF));
}

int t_ready(TID thread_id)
/*----------------------------------------------------------------------------+
| REQUIRES: The TID of thread to make ready                                   |
| MODIFIES: The ready_q, block_q                                              |
| EFFECTS:  Moves thread from block_q to ready_q returns 0 on success -1 on   |
|           failure                                                           |
+----------------------------------------------------------------------------*/
{
    extern LIST *ready_q;
    extern LIST *block_q;
    int list_position = 0, found_flag = FALSE;
    LIST *look_up, *node;
    THREAD *thread_ptr;
    int old_priority;
#ifdef DEBUG
    LIST *listcopy;
#endif

    old_priority = enter_crit();
    look_up = block_q;
    node = create_list();
    debug("t_ready - looking for thread[%d] on block_q", thread_id);
    while (!list_is_empty(look_up) && (found_flag != TRUE))
    {
	/* search block list for the thread */
	thread_ptr = node_item(look_up);
	debug("t_ready - examining thread[%d]", thread_ptr->id);
	list_position++;
	if (thread_ptr->id == thread_id)
	{
	    debug("t_ready - found thread[%d] on block_q", thread_ptr->id);
	    found_flag = TRUE;
	    node = look_up;
	}
	look_up = next_node(look_up);
    }

#ifdef DEBUG
    aprintf("\nThe following threads remain on blocked queue\n");
    listcopy = block_q;
    while (!list_is_empty(listcopy))
    {
	thread_ptr = node_item(listcopy);
	aprintf("\ttid %d\n", thread_ptr->id);
	listcopy = listcopy->next;
    }
    aprintf("\nThe following threads remain on ready queue\n");
    listcopy = ready_q;
    while (!list_is_empty(listcopy))
    {
	thread_ptr = node_item(listcopy);
	aprintf("\t tid %d\n", thread_ptr->id);
	listcopy = listcopy->next;
    }
    aprintf("num_created = %d\n", num_created);
    aprintf("num_destroyed = %d\n", num_destroyed);
#endif
    if (found_flag == TRUE)
    {
	/* put on ready list and delete from block q */

	thread_ptr = node_item(node);
	debug("t_ready - adding thread_id[%d] to ready list", thread_ptr->id);
	ready_q = insert_at_end(ready_q, sizeof(THREAD), node->data);
	debug("t_ready - about to remove node %d from block_q", list_position);
	block_q = delete_Nth(block_q, list_position);
#ifdef DEBUG
	aprintf("\nThe following threads remain on blocked queue\n");
	listcopy = block_q;
	while (!list_is_empty(listcopy))
	{
	    thread_ptr = node_item(listcopy);
	    aprintf("\ttid %d\n", thread_ptr->id);
	    listcopy = listcopy->next;
	}
	aprintf("\nThe following threads remain on ready queue\n");
	listcopy = ready_q;
	while (!list_is_empty(listcopy))
	{
	    thread_ptr = node_item(listcopy);
	    aprintf("\t tid %d\n", thread_ptr->id);
	    listcopy = listcopy->next;
	}
	aprintf("num_created = %d\n", num_created);
	aprintf("num_destroyed = %d\n", num_destroyed);
#endif
	exit_crit(old_priority);
	return (0);
    }
    else
    {
	debug("t_ready - didn't find thread_id[%d] on block_q", thread_id);
	exit_crit(old_priority);
	return (-1);
    }
}

TID t_myid(void)
/*----------------------------------------------------------------------------+
| REQUIRES: nothing                                                           |
| MODIFIES: nothing                                                           |
| EFFECTS: returns the TID of thread                                          |
+----------------------------------------------------------------------------*/
{
    extern LIST *ready_q;
    THREAD *thread_ptr;

    debug("t_myid - about to return id of thread");
    thread_ptr = node_item(ready_q);
    return (thread_ptr->id);
}

void scheduler(void)
/*----------------------------------------------------------------------------+
| REQUIRES: nothing                                                           |
| MODIFIES: ready_q, created processes                                        |
| EFFECTS: takes next ready process and resumes it process are run in a round |
|          robin sequence                                                     |
+----------------------------------------------------------------------------*/
{
    extern LIST *ready_q;
    extern LIST *block_q;
    LIST *listcopy;
    int blocked = 0;
    int deadlocked = FALSE;
    THREAD *thread_ptr, *blocked_ptr;
    struct timeval quantum;

    quantum.tv_sec = 0;
    quantum.tv_usec = QUANTUM;

#ifdef DEBUG
    listcopy = ready_q;
    while (!list_is_empty(listcopy))
    {
	thread_ptr = node_item(listcopy);
	debug("scheduler - ready_q = process%d", thread_ptr->id);
	listcopy = listcopy->next;
    }
#endif

    while (!list_is_empty(ready_q))	/* loops till ready list is empty */
    {

	thread_ptr = node_item(ready_q);

	if (lwp_resume(thread_ptr->thread) == -1)
	{
	    aprintf("scheduler - cannot resume process %d\n", thread_ptr->id);
	    pod_exit(1);
	}
	else
	{
	    debug("scheduler - staged to resume thread %d", thread_ptr->id);
	    debug("scheduler - going to sleep");
	    lwp_sleep(&quantum);
	    debug("scheduler - waking up");
	}



	if (lwp_ping(thread_ptr->thread) == 0)
	{
	    /*
	     * process is still alive so check if it was put on the blocked
	     * list if it is don't add to ready list just start next thread
	     */

	    debug("scheduler - process [%d] still alive, is it blocked?",
		  thread_ptr->id);
	    listcopy = block_q;
	    while (!list_is_empty(listcopy))
	    {
		blocked_ptr = node_item(listcopy);
		if (SAMETHREAD(thread_ptr->thread, blocked_ptr->thread))
		{
		    debug("scheduler - thread was blocked");
		    blocked = TRUE;
		}
		listcopy = listcopy->next;
	    }

	    if (!blocked)
	    {
		lwp_suspend(thread_ptr->thread);
		debug("scheduler - process id %d not blocked so put on ready_q",
		      thread_ptr->id);
		ready_q = insert_at_end(ready_q, sizeof(THREAD), thread_ptr);
		ready_q = delete_node(ready_q);
	    }
	}
	else
	    ready_q = delete_node(ready_q);	/* process is finished */
	blocked = FALSE;



    }

    debug("scheduler - empty ready_q");	/* ready list empty scheduler exiting */

    /*
     * ready queue is empty so let's determine deadlock or not
     */
    if (!(list_is_empty(block_q)))
    {
	deadlocked = TRUE;
	aprintf("DEADLOCK - HALTING ON ERROR CONDITION 3\n");
    }
    else
    {
	deadlocked = FALSE;
	aprintf("OS4U Terminating with no error condition\n");
    }
    aprintf("current process scheduling subsystem status\n");
    aprintf("--------------------------------------------------------\n");
    aprintf("%10s %10s %10s %10s\n",
	    "created", "completed", "ready", "blocked");
    aprintf("%10d %10d %10d %10d\n",
    num_created, num_destroyed, list_length(ready_q), list_length(block_q));
    aprintf("\tThe following threads remain on blocked queue\n\t");
    listcopy = block_q;
    while (!list_is_empty(listcopy))	/* dump block_q */
    {
	thread_ptr = node_item(listcopy);
	aprintf("tid%d ", thread_ptr->id);
	listcopy = listcopy->next;
    }
    aprintf("\n");
    dump_sem_list();
    ready_q = destroy_list(ready_q);
    block_q = destroy_list(block_q);
    sem_shutdown();
    unmmalloc();		/* return memory to unix */
    if (deadlocked == TRUE)
	pod_exit(3);
    else
	pod_exit(0);
}


void t_init(void)
/*----------------------------------------------------------------------------+
| REQUIRES: nothing                                                           |
| MODIFIES: ready_q, block_q                                                  |
| EFFECTS: initializes ready_q and block_q                                    |
+----------------------------------------------------------------------------*/
{
    extern LIST *ready_q;
    extern LIST *block_q;
    debug("t_init - initializing queues");
    ready_q = create_list();
    block_q = create_list();
    debug("t_init - queue initialization OK");
}
