/* MEM.C */

#include "debug.h"
#include "crit.h"
#include "list.h"
#include "mem.h"
#include "sem.h"
#include "util.h"

BUFFER *buf_list;

void mmalloc(int num_blocks)
/*----------------------------------------------------------------------------+
| REQUIRES: nothing                                                           |
| MODIFIES: nothing                                                           |
| EFFECTS:  builds a list of 200 free buffers for a total of 1280 bytes       |
+----------------------------------------------------------------------------*/
{
    extern BUFFER *buf_list;
    char *buf;
    register long int i;
    int old_priority;

    old_priority = enter_crit();
    /*
     * create a buffer list
     */
    buf_list = create_list();
    /*
     * Create a semaphore with name BUF_NAME(defined in mem.h) with an
     * initial count of num_blocks
     */
    s_create(BUF_NAME, num_blocks);

    /*
     * allocate num_blocks buffers one at a time
     */
    for (i = 1; i <= num_blocks; i++)
    {
	if ((buf = (char *) malloc(64)) == NULL)
	{
	    /*
	     * if there is an error using malloc to get host system memory
	     * then destroy list and halt
	     */
	    debug("mmalloc - memory allocation failed - deallocating");
	    buf_list = destroy_list(buf_list);
	    debug("mmalloc - list deallocated - halting");
	    pod_exit(1);
	}
	else
	{
	    /*
	     * if a buffer is allocated successfully place it on the free
	     * list
	     */
	    buf_list = add_node(buf_list, sizeof(buf), buf);
	    debug("mmalloc - allocated %ld blocks of memory for a total of %ld bytes", i, i * 64L);
	}

    }
    exit_crit(old_priority);
}

BUFFER *b_get(void)
/*----------------------------------------------------------------------------+
| REQUIRES: nothing                                                           |
| MODIFIES: nothing                                                           |
| EFFECTS:  returns a pointer to a 64 byte buffer if available, will block and|
|           wait for a buffer to become available                             |
+----------------------------------------------------------------------------*/
{
    BUFFER *buf;
    extern BUFFER *buf_list;
    SID s;
    int old_priority;

    old_priority = enter_crit();
    s = s_open(BUF_NAME);
    if ((s_wait(s)) == -1)
	aprintf("b_get - error opening/downing BUF_NAME\n");
    debug("b_get - assigning buffer for return to user");
    /*
     * give the user a pointer to the buffer
     */
    buf = buf_list->data;
    debug("b_get - assigned buffer for return to user");
    debug("b_get - removing buffer from free list");
    /*
     * delete the buffer from our free list
     */
    buf_list = delete_node(buf_list);
    debug("b_get - buffer successfully removed from free list");
    debug("b_get - size of remaining free list = %d", list_length(buf_list));
    debug("b_get - returning buffer to user");
    /*
     * return the pointer to the buffer to the user
     */
    if ((s_close(s)) == -1)
	aprintf("b_get - error closing BUF_NAME");
    exit_crit(old_priority);
    return (buf);
}

int b_release(BUFFER * buf)
/*----------------------------------------------------------------------------+
| REQUIRES: buf_list is initialized and b has been previously allocated       |
| MODIFIES: buf and buf_list                                                  |
| EFFECTS:  releases the buffer b making it available to other threads, will  |
|           return 0 on success and -1 on failure                             |
+----------------------------------------------------------------------------*/
{
    int before, after;
    extern BUFFER *buf_list;
    SID s;
    int old_priority;

    old_priority = enter_crit();
    debug("b_release - releasing buffer");
    before = list_length(buf_list);
    debug("b_release - length of free list prior to return of node = %d", before);
    debug("b_release - adding node to free list");
    buf_list = add_node(buf_list, sizeof(buf), buf);
    debug("b_release - returned from adding node to free list");
    after = list_length(buf_list);
    debug("b_release - length of free list after return of node = %d", after);
    debug("b_release - disposing of memory via delete_node");
    buf = delete_node(buf);
    debug("b_release - memory disposed of properly");
    debug("b_release - buffer successfully released");
    s = s_open(BUF_NAME);
    if ((s_signal(s)) == -1)
    {
	aprintf("b_release - error UPing BUF_NAME");
	exit_crit(old_priority);
	return (-1);
    }
    if (after == before + 1)
    {
	if ((s_close(s)) == -1)
	    aprintf("b_release - error closing BUF_NAME");
	exit_crit(old_priority);
	return (0);
    }

}

void unmmalloc(void)
/*----------------------------------------------------------------------------+
| REQUIRES: buf_list has been allocated by mmalloc()                          |
| MODIFIES: buf_list                                                          |
| EFFECTS:  returns all memory allocated by mmalloc to system                 |
+----------------------------------------------------------------------------*/
{
    extern BUFFER *buf_list;
    int old_priority;

    old_priority = enter_crit();
    debug("unmmalloc - returning free list to host system");
    buf_list = destroy_list(buf_list);
    debug("unmmalloc - free list successfully returned to host system");
    exit_crit(old_priority);
}
