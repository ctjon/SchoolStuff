/* CRIT.H */

#ifndef __CRITH__
#define __CRITH__
#include "maxprio.h"

int enter_crit();
/*-----------------------------------------------------------------------------+
| REQUIRES: this procedure must be called from within a thread as per lwp      |
| MODIFIES: the priority of the current thread                                 |
| EFFECTS:  places the current thread at the highest lwp priority level thus   |
|           preventing it from being preempted by another thread if its quantum|
|           expires. RETURNS the new priority level if successful else aborts  |
+-----------------------------------------------------------------------------*/

void exit_crit(int old_priority);
/*-----------------------------------------------------------------------------+
| REQUIRES: this procedure must be called from within a thread as per lwp      |
| MODIFIES: the priority of the current thread                                 |
| EFFECTS:  places the current thread at the lwp priority level specified by   |
|           old_priority thus returning it to its original priority an removing|
|           it from the critical section.  WARNING this procedure is intended  |
|           to be called with the value returned from enter_crit() above.  IT  |
|           is possible that this procedure could be used to set priorities to |
|           any level!                                                         |
+-----------------------------------------------------------------------------*/

#endif				/* __CRITH__ */
