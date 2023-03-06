/* SEM.H */

#ifndef __SEMH__
#define __SEMH__

#include "list.h"
typedef int SID;

typedef struct sem_node
{
    SID semid;
    int current_count;
    int initial_count;
    int sem_name;
    int s_opened_by;
    LIST *sblocked;
}        SEMAPHORE;


void s_init(void);
/*-----------------------------------------------------------------------------+
| REQUIRES: nothing                                                            |
| MODIFIES: nothing                                                            |
| EFFECTS:  s_init creates a semaphore list so that we have storage for our    |
|           semaphores.                                                        |
+-----------------------------------------------------------------------------*/

int s_create(int sem_name, int initial_count);
/*-----------------------------------------------------------------------------+
| REQUIRES: a valid name and initial count input                               |
| MODIFIES: semaphore_list                                                     |
| EFFECTS:  s_create is an atomic operation that creates a semaphore with name |
|           n and count c. s_create returns 0 if successful and -1 otherwise   |
+-----------------------------------------------------------------------------*/

int s_destroy(int sem_name);
/*-----------------------------------------------------------------------------+
| REQUIRES: a valid sem_name(will check validity for you)                      |
| MODIFIES: semaphore_list                                                     |
| EFFECTS:  s_destroy is an atomic operation that destroys the semaphore with  |
|           name n.  s_destroy returns 0 if successful and -1 otherwise        |
+-----------------------------------------------------------------------------*/

SID s_open(int sem_name);
/*-----------------------------------------------------------------------------+
| REQUIRES: a valid sem_name(will check validity for you)                      |
| MODIFIES: the s_open_by count stored in the semaphore                        |
| EFFECTS:  s_open is an atomic operation that opens the semaphore with name   |
|           n, and returns the SID which identifies the semaphore, thus        |
|           binding the SID to the semaphore name.  -1 is returned on failure  |
+-----------------------------------------------------------------------------*/

int s_close(SID semid);
/*-----------------------------------------------------------------------------+
| REQUIRES: a valid semid(will check validity for you)                         |
| MODIFIES: the s_open_by variable stored in the semaphore                     |
| EFFECTS:  s_close is an atomic operation which closes the semaphore with SID |
|           s and returns 0 on success and -1 on failure                       |
+-----------------------------------------------------------------------------*/

int s_signal(SID semid);
/*-----------------------------------------------------------------------------+
| REQUIRES: a valid semid(validity will be checked for you)                    |
| MODIFIES: the semaphore                                                      |
| EFFECTS:  s_signal is an atomic operation which signals the semaphore with   |
|           SID s, releasing a waiting thread, if any exist.  Returns 0 on     |
|           success and -1 on failure. (performs an UP operation)              |
+-----------------------------------------------------------------------------*/

int s_wait(SID semid);
/*-----------------------------------------------------------------------------+
| REQUIRES: a valid semid(validity will be checked for you)                    |
| MODIFIES: the semaphore                                                      |
| EFFECTS:  s_wait is an atomic operation that waits on a semaphore with SID s |
|           Returns 0 on success and -1 on failure(performs a DOWN operation)  |
+-----------------------------------------------------------------------------*/

void dump_sem_list(void);
void sem_shutdown(void);

#endif				/* __SEMH__ */
