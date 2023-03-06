/* SCHED.H */

#ifndef __SCHEDH__
#define __SCHEDH__

typedef int TID;

#include "list.h"

#include <lwp/lwp.h>
#include <lwp/stackdep.h>


LIST *block_q;
LIST *ready_q;
#define QUANTUM 10
#define USER 0

typedef struct thread_node
{
    thread_t thread;
    TID id;
}           THREAD;


TID t_create(void *f);
/*----------------------------------------------------------------------------+
| REQUIRES: t_init has been called once first                                 |
| MODIFIES: ready_q                                                           |
| EFFECTS: creates a thread, places it on ready_q and returns the id of thread|
|          returns 0 on success -1 on failure                                 |
+----------------------------------------------------------------------------*/

int t_destroy(void);
/*----------------------------------------------------------------------------+
| REQUIRES: nothing                                                           |
| MODIFIES: calling thread and ready_q                                        |
| EFFECTS:  destroys the calling thread and returns 0 on success -1 on failure|
+----------------------------------------------------------------------------*/

int t_block(void);
/*----------------------------------------------------------------------------+
| REQUIRES: nothing                                                           |
| MODIFIES: calling thread, ready_q, block_q                                  |
| EFFECTS: blocks the calling thread, removing it from ready_q and putting it |
|          on block_q, returns 1 on success 0 on failure                      |
+----------------------------------------------------------------------------*/

int t_ready(TID t);
/*----------------------------------------------------------------------------+
| REQUIRES: The TID of thread to make ready                                   |
| MODIFIES: The ready_q, block_q                                              |
| EFFECTS: Moves thread from block_q to ready_q returns 0 on success -1 on    |
|          failure                                                            |
+----------------------------------------------------------------------------*/

TID t_myid(void);
/*----------------------------------------------------------------------------+
| REQUIRES: nothing                                                           |
| MODIFIES: nothing                                                           |
| EFFECTS: returns the TID of thread or -1 on failure                         |
+----------------------------------------------------------------------------*/

void scheduler(void);
/*----------------------------------------------------------------------------+
| REQUIRES: nothing                                                           |
| MODIFIES: ready_q, created processes                                        |
| EFFECTS: takes next ready process and resumes it process are run in a round |
|          robin sequence                                                     |
+----------------------------------------------------------------------------*/

void t_init(void);
/*----------------------------------------------------------------------------+
| REQUIRES: nothing                                                           |
| MODIFIES: ready_q, block_q                                                  |
| EFFECTS: initializes ready_q and block_q                                    |
+----------------------------------------------------------------------------*/

#endif				/* __SCHEDH__ */
