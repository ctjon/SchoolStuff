/* IPC.C */

#include "ipc.h"
#include "util.h"

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

void m_send(TID tid, BUFFER * message)
/*-----------------------------------------------------------------------------+
| REQUIRES: tid of receiving thread and the buffer containing the message      |
| MODIFIES: the mailbox of the receiving thread                                |
| EFFECTS:  places the message at the tail end of the message list in the      |
|           mailbox for the thread t.                                          |
+-----------------------------------------------------------------------------*/
{
    extern LIST *mail_box_list;
    MBOX *mbox_ptr, *mbox_node;
    MNODE *message_node;
    SID s;
    int old_priority;
    register int i;

    old_priority = enter_crit();
    if (!mbox_exists(tid))
	create_mbox(tid);
    for (i = 1; i <= list_length(mail_box_list); i++)
    {
	mbox_ptr = node_item(mail_box_list);
	if (tid == mbox_ptr->tid)
	{
	    if ((message_node = (MNODE *) malloc(sizeof(MNODE))) == NULL)
	    {
		aprintf("m_send - insufficient memory - exiting!\n");
		pod_exit(1);
	    }
	    message_node->sending_thread = t_myid();
	    message_node->mbuf = b_get();
	    sprintf(((char *) message_node->mbuf), "%-64s", message);
	    debug("m_send - buffer now contains \n[%s] from [TID%d]",
		  message_node->mbuf, message_node->sending_thread);
	    ((LIST *) (mbox_ptr->message_list)) = insert_at_end(((LIST *) (mbox_ptr->message_list)), sizeof(MNODE), message_node);
	    debug("m_send - added to list");
	    s = s_open(mbox_ptr->sem_name);
	    debug("m_send - opening semaphore");
	    if ((s_signal(s)) == -1)
		aprintf("m_send - error signaling sem %d\n",
			mbox_ptr->sem_name);
	    if ((s_close(s)) == -1)
		aprintf("m_send - error closing sem %d\n", mbox_ptr->sem_name);
	}
	mail_box_list = insert_at_end(mail_box_list, sizeof(MBOX), mbox_ptr);
	mail_box_list = delete_node(mail_box_list);
    }
    debug("m_send - exiting");
    exit_crit(old_priority);
}

void m_receive(TID * tid, BUFFER * message)
/*-----------------------------------------------------------------------------+
| REQUIRES: pointer to the tid of the sending thread and a buffer m to receive |
|           the message into.                                                  |
| MODIFIES: m and the mailbox of the thread t                                  |
| EFFECTS:  copies the first message from the mailbox for the receiving thread |
|           into the buffer m and returns the tid of the sending thread in t   |
+-----------------------------------------------------------------------------*/
{
    extern LIST *mail_box_list;
    MBOX *mbox_ptr;
    MNODE *message_node;
    LIST *mlist_ptr, *list_copy;
    SID s;
    int found = FALSE;
    int old_priority;
    register int i;

    old_priority = enter_crit();
    if (!mbox_exists(t_myid()))
	create_mbox(t_myid());
    list_copy = mail_box_list;
    while ((!list_is_empty(list_copy)) && (found == FALSE))
    {
	mbox_ptr = node_item(list_copy);
	if (mbox_ptr->tid == t_myid())
	{
	    found = TRUE;
	    debug("m_receive - found our node - waiting");
	    s = s_open(mbox_ptr->sem_name);
	    if ((s_wait(s)) == -1)
		aprintf("m_receive - error signaling sem %d\n",
			mbox_ptr->sem_name);
	    if ((s_close(s)) == -1)
		aprintf("m_receive - error closing sem %d\n",
			mbox_ptr->sem_name);
	}
	list_copy = next_node(list_copy);
    }
    for (i = 1; i <= list_length(mail_box_list); i++)
    {
	mbox_ptr = node_item(mail_box_list);
	if (mbox_ptr->tid == t_myid())
	{
	    mlist_ptr = ((LIST *) (mbox_ptr->message_list));
	    debug("m_receive - assigning MNODE");
	    if (list_is_empty(mlist_ptr))
		debug("m_receive - about to assign MNODE from empty list");
	    if (!list_is_empty(mlist_ptr))
	    {
		message_node = ((MNODE *) node_item(mlist_ptr));
		sprintf(((char *) message), "%-64s", ((char *) message_node->mbuf));
		*tid = message_node->sending_thread;
		debug("m_receive - received buffer \n[%s] from [TID%d]",
		      message_node->mbuf, message_node->sending_thread);
		if (b_release(message_node->mbuf) == -1)
		    aprintf("m_receive - error releasing buffer\n");
		((LIST *) (mbox_ptr->message_list)) = delete_node((LIST *) (mbox_ptr->message_list));
		debug("m_receive - node deleted from message_list OK");
	    }
	}
	mail_box_list = insert_at_end(mail_box_list, sizeof(MBOX), mbox_ptr);
	mail_box_list = delete_node(mail_box_list);
    }
    debug("m_receive - exiting");
    exit_crit(old_priority);
}

int create_mbox(TID tid)
/*-----------------------------------------------------------------------------+
| REQUIRES: ipc_init() has been run                                            |
| MODIFIES: mail_box_list                                                      |
| EFFECTS:  creates a mailbox for tid and inserts it in the mail_box_list      |
+-----------------------------------------------------------------------------*/
{
    extern LIST *mail_box_list;
    LIST *list_copy;
    MBOX *mbox_ptr, *mbox_node;
    int old_priority;

    old_priority = enter_crit();
    /*
     * check to make sure that a mailbox does not already exist for this
     * thread
     */
    list_copy = mail_box_list;
    while (!list_is_empty(list_copy))
    {
	mbox_ptr = node_item(list_copy);
	if (tid == mbox_ptr->tid)
	{
	    debug("create_mbox - mailbox for TID%d already exists", tid);
	    return (-1);
	}
	list_copy = next_node(list_copy);
    }
    /*
     * no mailbox exists so create one
     */
    if ((mbox_node = (MBOX *) malloc(sizeof(MBOX))) == NULL)
    {
	aprintf("create_mbox - insufficient memory - exiting!\n");
	pod_exit(1);
    }
    mbox_node->tid = tid;
    s_create(tid + 1000, 0);
    mbox_node->sem_name = (tid + 1000);
    (LIST *) mbox_node->message_list = (LIST *) create_list();
    mail_box_list = insert_at_end(mail_box_list, sizeof(MBOX), mbox_node);
    exit_crit(old_priority);
    return (0);
}

int mbox_exists(TID tid)
/*-----------------------------------------------------------------------------+
| REQUIRES: ipc_init() has been run                                            |
| MODIFIES: nothing                                                            |
| EFFECTS:  creates the required ipc list structures                           |
+-----------------------------------------------------------------------------*/
{
    extern LIST *mail_box_list;
    LIST *list_copy;
    MBOX *mbox_ptr;

    list_copy = mail_box_list;
    while (!list_is_empty(list_copy))
    {
	mbox_ptr = node_item(list_copy);
	if (tid == mbox_ptr->tid)
	{
	    debug("mbox_exists - mailbox for TID%d already exists", tid);
	    return (TRUE);
	}
	list_copy = next_node(list_copy);
    }
    debug("mbox_exists - mailbox for TID%d does not exist", tid);
    return (FALSE);
}

void ipc_init(void)
/*-----------------------------------------------------------------------------+
| REQUIRES: nothing                                                            |
| MODIFIES: nothing                                                            |
| EFFECTS:  creates the required ipc list structures                           |
+-----------------------------------------------------------------------------*/
{
    mail_box_list = create_list();
    aprintf("OS4U IPC Subsystem Initialization Complete\n");
}

void ipc_shutdown(void)
/*-----------------------------------------------------------------------------+
| REQUIRES: ipc_init has been run                                              |
| MODIFIES: mail_box_list                                                      |
| EFFECTS:  destroys the ipc list structures                                   |
+-----------------------------------------------------------------------------*/
{
    mail_box_list = destroy_list(mail_box_list);
    aprintf("OS4U IPC Subsystem Destruction Complete\n");
}

void ipc_stat(void)
/*-----------------------------------------------------------------------------+
| REQUIRES: ipc_init has been run                                              |
| MODIFIES: nothing                                                            |
| EFFECTS:  dumps the current status of the ipc subsystem                      |
+-----------------------------------------------------------------------------*/
{
    extern LIST *mail_box_list;
    LIST *listcopy, *mlist_copy;
    MBOX *mbox_ptr;
    MNODE *mlist_node;
    char buf[64];
    int old_priority;

    old_priority = enter_crit();
    listcopy = mail_box_list;
    aprintf("\nCurrent IPC Subsystem Status");
    aprintf("\nSTART--------------------------------------------------\n");
    while (!list_is_empty(listcopy))
    {


	mbox_ptr = node_item(listcopy);
	aprintf("%-10s %-10s %-15s\n", "TID", "SEM_NAME", "MESSAGE COUNT");
	aprintf("%-10d %-10d %-15d\n", mbox_ptr->tid, mbox_ptr->sem_name, list_length((LIST *) mbox_ptr->message_list));
	aprintf("ipc_stat - message list follows\n");
	mlist_copy = ((LIST *) (mbox_ptr->message_list));
	while (!list_is_empty(mlist_copy))
	{
	    mlist_node = ((MNODE *) node_item(mlist_copy));
	    aprintf(" [%s] from [TID%d]\n", mlist_node->mbuf, mlist_node->sending_thread);
	    mlist_copy = next_node(mlist_copy);
	}
	aprintf("\n");
	listcopy = next_node(listcopy);
    }
    aprintf("\nEND ----------------------------------------------------\n");
    exit_crit(old_priority);
}
