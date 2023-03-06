/* master.c */

#include <stdio.h>
#include <string.h>
#include "spooler.h"
#include "mem.h"
#include "command.h"
#include "ipc.h"
#include "sched.h"
#include "util.h"

TID Master, input_id, output_id;

void master_thread(void)
/*----------------------------------------------------------------------------+
| REQUIRES: nothing                                                           |
| MODIFIES: nothing                                                           |
| EFFECTS: starts the input spooler, output spooler, and command proccessors  |
|             as needed                                                       |
+----------------------------------------------------------------------------*/
{
    extern TID input_id, output_id, Master;
    TID cp_id, next;
    BUFFER *buf;
    char str[64];

    debug("master - entered master_thread");
    Master = t_myid();
    buf = b_get();
    input_id = t_create(input_spool);
    t_ready(input_id);
    output_id = t_create(output_spool);
    t_ready(output_id);
    for (;;)
    {
	debug("master - about to call m_receive");
	m_receive(&next, buf);
	debug("master - received message\n[%s] from [TID%d]", buf, next);
	sprintf(str, "%-64s", buf);
	debug("master - about to compare string");
	if (strncmp(str, "Create_Task", 11) == 0)
	{
	    debug("master - about call processor");
	    cp_id = t_create(processor);
	    t_ready(cp_id);
	    debug("master - about to called processor ");
	    sprintf(str, "%-64d", cp_id);
	    debug("master - putting id in string");
	    sprintf((char *) buf, "%-64s", str);
	    debug("master - calling m_send");
	    m_send(input_id, buf);
	    debug("master - return from m_send");
	}
	else
	    fprintf(stderr, "%s\n", "BOGUS MESSAGE");
    }
}
