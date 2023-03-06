/* IPC.H */

#ifndef __IPCH__
#define __IPCH__

#include "list.h"
#include "mem.h"
#include "sched.h"
#include "sem.h"

LIST *mail_box_list;

typedef struct mail_box
{
    TID tid;
    int sem_name;
    LIST *message_list;
}        MBOX;

typedef struct message_node
{
    TID sending_thread;
    BUFFER *mbuf;
}            MNODE;


void m_send(TID tid, BUFFER * message);
/*-----------------------------------------------------------------------------+
| REQUIRES: tid of receiving thread and the buffer containing the message      |
| MODIFIES: the mailbox of the receiving thread                                |
| EFFECTS:  places the message at the tail end of the message list in the      |
|           mailbox for the thread t.                                          |
+-----------------------------------------------------------------------------*/

void m_receive(TID * tid, BUFFER * message);
/*-----------------------------------------------------------------------------+
| REQUIRES: pointer to the tid of the sending thread and a buffer m to receive |
|           the message into.                                                  |
| MODIFIES: m and the mailbox of the thread t                                  |
| EFFECTS:  copies the first message from the mailbox for the receiving thread |
|           into the buffer m and returns the tid of the sending thread in t   |
+-----------------------------------------------------------------------------*/

void ipc_init(void);
/*-----------------------------------------------------------------------------+
| REQUIRES: nothing                                                            |
| MODIFIES: nothing                                                            |
| EFFECTS:  creates the required ipc list structures                           |
+-----------------------------------------------------------------------------*/

void ipc_shutdown(void);
/*-----------------------------------------------------------------------------+
| REQUIRES: ipc_init has been run                                              |
| MODIFIES: mail_box_list                                                      |
| EFFECTS:  destroys the ipc list structures                                   |
+-----------------------------------------------------------------------------*/

void ipc_stat(void);
/*-----------------------------------------------------------------------------+
| REQUIRES: ipc_init has been run                                              |
| MODIFIES: nothing                                                            |
| EFFECTS:  dumps the current status of the ipc subsystem                      |
+-----------------------------------------------------------------------------*/

#endif
