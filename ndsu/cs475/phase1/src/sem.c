/* SEM.C */

#include <stdio.h>
#include "crit.h"
#include "debug.h"
#include "list.h"
#include "maxprio.h"
#include "sched.h"
#include "sem.h"
#include "util.h"

SID num_SIDs = 0;
LIST *semaphore_list;

void s_init(void)
/*-----------------------------------------------------------------------------+
| REQUIRES: nothing                                                            |
| MODIFIES: nothing                                                            |
| EFFECTS:  s_init creates a semaphore list so that we have storage for our    |
|           semaphores.                                                        |
+-----------------------------------------------------------------------------*/
{
    semaphore_list = create_list();
    aprintf("s_init - semaphore initialization complete\n");
}

int s_create(int sem_name, int initial_count)
/*-----------------------------------------------------------------------------+
| REQUIRES: a valid name and initial count input                               |
| MODIFIES: semaphore_list                                                     |
| EFFECTS:  s_create is an atomic operation that creates a semaphore with name |
|           n and count c. s_create returns 0 if successful and -1 otherwise   |
+-----------------------------------------------------------------------------*/
{
    SEMAPHORE *node, *sem_ptr;
    LIST *lookup_list;
    extern LIST *semaphore_list;
    int old_priority;

    /*
     * Take over at highest priority
     */
    old_priority = enter_crit();
    /*
     * determine if a semaphore already exists with sem_name
     */
    lookup_list = semaphore_list;
    while (!list_is_empty(lookup_list))
    {
	sem_ptr = node_item(lookup_list);
	if (sem_name == sem_ptr->sem_name)
	{
	    aprintf("s_create - error SID %d already exists\n", sem_name);
	    /*
	     * restore previous priority prior and return -1
	     */
	    exit_crit(old_priority);
	    return (-1);
	}
	lookup_list = next_node(lookup_list);
    }
    /*
     * we have a new semaphore so increment the number of semaphores and put
     * it on the list of semaphores
     */
    if ((node = (SEMAPHORE *) malloc(sizeof(SEMAPHORE))) == NULL)
	aprintf("s_create - insufficient memory available - exiting!\n"), pod_exit(1);
    else
    {
	node->semid = num_SIDs;
	node->current_count = initial_count;
	node->initial_count = initial_count;
	node->sem_name = sem_name;
	debug("s_create - created semaphore semid = %d, name = %d, and count %d"
	      ,node->semid, node->sem_name, node->initial_count);
	node->sblocked = (LIST *) create_list();
	node->s_opened_by = 0;
	semaphore_list = insert_at_end(semaphore_list, sizeof(SEMAPHORE), node);
	debug("s_create - added semaphore %d to semaphore list", node->semid);
	num_SIDs++;
	/*
	 * restore previous priority prior and return 0
	 */
	exit_crit(old_priority);
	return (0);
    }
}

int s_destroy(int sem_name)
/*-----------------------------------------------------------------------------+
| REQUIRES: a valid sem_name(will check validity for you)                      |
| MODIFIES: semaphore_list                                                     |
| EFFECTS:  s_destroy is an atomic operation that destroys the semaphore with  |
|           name n.  s_destroy returns 0 if successful and -1 otherwise        |
+-----------------------------------------------------------------------------*/
{
    SEMAPHORE *node, *sem_ptr;
    LIST *lookup_list;
    extern LIST *semaphore_list;
    int old_priority;

    /*
     * Take over at highest priority
     */
    old_priority = enter_crit();
    /*
     * find the actual semaphore in the list and see if we can delete it
     */
    while (!list_is_empty(semaphore_list))
    {
	sem_ptr = node_item(semaphore_list);
	if (sem_name == sem_ptr->sem_name)	/* found it */
	{
	    debug("s_destroy - found %d attempting to delete", sem_ptr->sem_name);
	    if ((list_is_empty((LIST *) sem_ptr->sblocked)) && (sem_ptr->s_opened_by == 0))
	    {
		(LIST *) sem_ptr->sblocked = destroy_list((LIST *) sem_ptr->sblocked);
		semaphore_list = delete_node(semaphore_list);
		num_SIDs--;
		/*
		 * restore previous priority prior and return 0
		 */
		exit_crit(old_priority);
		return (0);
	    }
	    else
	    {
		/*
		 * list of semaphores is not empty so we cannot destroy
		 * restore previous priority prior to exit
		 */
		aprintf("s_destroy - attempted destroy of inuse semaphore\n");
		aprintf("s_destroy - semaphore must be free to be destroyed\n");
		exit_crit(old_priority);
		return (-1);
	    }
	}
	semaphore_list = delete_node(semaphore_list);
    }
    /*
     * semaphore does not exist on the list so return -1 and restore previous
     * priority prior to exit
     */
    aprintf("s_destroy - attempt to delete an invalid SID\n");
    aprintf("s_destroy - sem_name = %d not found\n", sem_name);
    exit_crit(old_priority);
    return (-1);
}

SID s_open(int sem_name)
/*-----------------------------------------------------------------------------+
| REQUIRES: a valid sem_name(will check validity for you)                      |
| MODIFIES: the s_open_by count stored in the semaphore                        |
| EFFECTS:  s_open is an atomic operation that opens the semaphore with name   |
|           n, and returns the SID which identifies the semaphore, thus        |
|           binding the SID to the semaphore name.  -1 is returned on failure  |
+-----------------------------------------------------------------------------*/
/*
 * finds a semaphore of name sem_name and returns the SID for that name and
 */
{
    SEMAPHORE *node, *sem_ptr;
    LIST *lookup_list;
    extern LIST *semaphore_list;
    int old_priority;

    /*
     * Take over at highest priority
     */
    old_priority = enter_crit();
    /*
     * find the semaphore in the semilist and return semid
     */
    lookup_list = semaphore_list;
    while (!list_is_empty(lookup_list))
    {
	sem_ptr = node_item(lookup_list);
	if (sem_name == sem_ptr->sem_name)	/* found it */
	{
	    debug("s_open - found %d and opening", sem_ptr->sem_name);
	    sem_ptr->s_opened_by++;
	    /*
	     * restore previous priority prior and return the semaphore id
	     */
	    exit_crit(old_priority);
	    return (sem_ptr->semid);
	}
	lookup_list = next_node(lookup_list);
    }
    /*
     * semaphore does not exist in the list so return -1 and restore previous
     * priority prior and return -1
     */
    aprintf("s_open - attempt to open an invalid SID\n");
    aprintf("s_open - sem_name = %d not found\n", sem_name);
    exit_crit(old_priority);
    return (-1);
}

int s_close(SID semid)
/*-----------------------------------------------------------------------------+
| REQUIRES: a valid semid(will check validity for you)                         |
| MODIFIES: the s_open_by variable stored in the semaphore                     |
| EFFECTS:  s_close is an atomic operation which closes the semaphore with SID |
|           s and returns 0 on success and -1 on failure                       |
+-----------------------------------------------------------------------------*/
{
    SEMAPHORE *node, *sem_ptr;
    LIST *lookup_list;
    extern LIST *semaphore_list;
    int old_priority;

    /*
     * Take over at highest priority
     */
    old_priority = enter_crit();
    /*
     * find the actual semaphore in the list and see if we can close it
     */
    while (!list_is_empty(semaphore_list))
    {
	sem_ptr = node_item(semaphore_list);
	if (semid == sem_ptr->semid)	/* found it */
	{
	    debug("s_close - found %d and closing", sem_ptr->semid);
	    sem_ptr->s_opened_by--;
	    /*
	     * restore previous priority prior to exit
	     */
	    exit_crit(old_priority);
	    return (0);
	}
	/*
	 * must be careful here - node is moved from front of semaphore_list
	 * to end of semaphore_list.  It is not possible to just advance the
	 * list because it is a global list of all the semaphores and
	 * advancing it may hose up other semaphores.  Cycling the nodes
	 * insures that no one is lost
	 */
	semaphore_list = insert_at_end(semaphore_list, sizeof(SEMAPHORE), sem_ptr);
	semaphore_list = delete_node(semaphore_list);
    }
    /*
     * semaphore does not exist in the list so return -1 restore previous
     * priority prior to exit
     */
    aprintf("s_close - attempt to close an invalid SID\n");
    aprintf("s_close - semid = %d not found\n", semid);
    exit_crit(old_priority);
    return (-1);
}

int s_wait(SID semid)
/*-----------------------------------------------------------------------------+
| REQUIRES: a valid semid(validity will be checked for you)                    |
| MODIFIES: the semaphore                                                      |
| EFFECTS:  s_wait is an atomic operation that waits on a semaphore with SID s |
|           Returns 0 on success and -1 on failure(performs a DOWN operation)  |
+-----------------------------------------------------------------------------*/
{
    extern LIST *semaphore_list;
    SEMAPHORE *sem_ptr;
    THREAD blocking;
    LIST *lookup_list;
    int old_priority;

    old_priority = enter_crit();
    lookup_list = semaphore_list;
    /*
     * look for semaphore with semid on semaphore list
     */
    while (!list_is_empty(lookup_list))
    {
	sem_ptr = node_item(lookup_list);
	if (semid == sem_ptr->semid)
	{
	    /*
	     * found semid on the semaphore_list so down it and decide
	     * whether or not to block the current thread
	     */
	    debug("s_wait - found %d and DOWNING", sem_ptr->sem_name);
	    sem_ptr->current_count--;
	    if (sem_ptr->current_count < 0)
	    {
		/*
		 * OK, the current count of the semaphore is =< 0 (note:
		 * current_count is decremented before compare, thus =<) so
		 * block the thread by placing it on the blocked queue for
		 * that semaphore and then calling tblock()
		 */
		blocking.thread = SELF;
		blocking.id = t_myid();
		((LIST *) (sem_ptr->sblocked)) = insert_at_end(((LIST *) (sem_ptr->sblocked)), sizeof(THREAD), &blocking);
		exit_crit(old_priority);
		return (t_block());
	    }
	    /*
	     * The current count was > 0 so we dont need to block anyone..
	     */
	    exit_crit(old_priority);
	    return (0);
	}
	/*
	 * advance the lookup_list
	 */
	lookup_list = next_node(lookup_list);
    }
    /*
     * the specified semaphore was not found on the semaphore list so
     * generate an error and return -1
     */
    aprintf("s_wait - error - semaphore %d not found on sem list\n", semid);
    exit_crit(old_priority);
    return (-1);		/* we did not find the semaphore on the list */
}

int s_signal(SID semid)
/*-----------------------------------------------------------------------------+
| REQUIRES: a valid semid(validity will be checked for you)                    |
| MODIFIES: the semaphore                                                      |
| EFFECTS:  s_signal is an atomic operation which signals the semaphore with   |
|           SID s, releasing a waiting thread, if any exist.  Returns 0 on     |
|           success and -1 on failure. (performs an UP operation)              |
+-----------------------------------------------------------------------------*/
{
    SEMAPHORE *sem_ptr;
    LIST *blist_ptr, *lookup_list;
    THREAD *blist_node;
    extern LIST *semaphore_list;
    int old_priority;

    old_priority = enter_crit();
    lookup_list = semaphore_list;
    /*
     * look for semaphore with semid on semaphore list
     */
    while (!list_is_empty(lookup_list))
    {
	sem_ptr = node_item(lookup_list);
	if (semid == sem_ptr->semid)
	{
	    /*
	     * found semid on the semaphore_list so UP it and check to see if
	     * we need to unblock the next thread which is waiting for this
	     * semaphore (if there are any)
	     */
	    debug("s_signal - found %d and UPPING", sem_ptr->sem_name);
	    sem_ptr->current_count++;
	    if (!list_is_empty(((LIST *) sem_ptr->sblocked)))
	    {
		/*
		 * retrieve the TID of the next thread on this semaphores
		 * blocked list and pass it to tready() so it can be run
		 */
		blist_ptr = (LIST *) (sem_ptr->sblocked);
		(LIST *) sem_ptr->sblocked = delete_node((LIST *) sem_ptr->sblocked);
		blist_node = (THREAD *) (blist_ptr->data);
		exit_crit(old_priority);
		return (t_ready((int) (blist_node->id)));
	    }
	    else
	    {
		/*
		 * there are no threads waiting for this semaphore so just
		 * return 0 and drive on
		 */
		exit_crit(old_priority);
		return (0);	/* nothing to do */
	    }
	}
	/*
	 * advance the lookup_list
	 */
	lookup_list = next_node(lookup_list);
    }
    /*
     * the specified semaphore was not found on the semaphore list so
     * generate an error and return -1
     */
    aprintf("s_signal - error - semaphore %d not found on sem list\n", semid);
    exit_crit(old_priority);
    return (-1);		/* we did not find the semaphore on the list */
}

void dump_sem_list(void)
{
    extern LIST *semaphore_list;
    LIST *listcopy, *blist_copy;
    SEMAPHORE *sem_ptr;
    THREAD *blist_node;

    listcopy = semaphore_list;
    aprintf("\ncurrent semaphore subsystem status");
    while (!list_is_empty(listcopy))
    {
	sem_ptr = node_item(listcopy);
	aprintf("\n--------------------------------------------------------\n");
	aprintf("%10s %10s %10s %10s %10s\n",
		"SID", "InitCnt", "CurrCnt", "Name", "#opens");
	aprintf("%10d %10d %10d %10d %10d\n",
		sem_ptr->semid, sem_ptr->initial_count,
		sem_ptr->current_count, sem_ptr->sem_name,
		sem_ptr->s_opened_by);
	aprintf("\tblocked ->");
	blist_copy = (LIST *) (sem_ptr->sblocked);
	while (!list_is_empty(blist_copy))
	{
	    blist_node = (THREAD *) (blist_copy->data);
	    aprintf(" tid%d ", (int) (blist_node->id));
	    blist_copy = next_node(blist_copy);
	}
	printf("\n");
	listcopy = next_node(listcopy);
    }
}

void sem_shutdown(void)
{
    semaphore_list = destroy_list(semaphore_list);
}
