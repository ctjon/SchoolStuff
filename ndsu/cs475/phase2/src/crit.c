/* CRIT.C */

#include <stdio.h>
#include <lwp/lwp.h>

#include "crit.h"
#include "maxprio.h"


int enter_crit(void)
/*-----------------------------------------------------------------------------+
| REQUIRES: this procedure must be called from within a thread as per lwp      |
| MODIFIES: the priority of the current thread                                 |
| EFFECTS:  places the current thread at the highest lwp priority level thus   |
|           preventing it from being preempted by another thread if its quantum|
|           expires. RETURNS the old priority level if successful else aborts  |
+-----------------------------------------------------------------------------*/
{
    int old_priority;

    old_priority = lwp_setpri(SELF, MAXPRIO);
    if (old_priority == -1)
    {
	fprintf(stderr, "%s\n",
		"enter_crit - error entering critical section - halting");
	pod_exit(1);
    }
    else
	return (old_priority);
}

void exit_crit(int old_priority)
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
{
    if ((lwp_setpri(SELF, old_priority)) == -1)
    {
	fprintf(stderr, "%s\n",
		"exit_crit - error exiting critical section - halting");
	pod_exit(1);
    }
}
