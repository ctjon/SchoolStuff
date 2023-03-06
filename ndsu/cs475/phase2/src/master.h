/* master.h */

#include <stdio.h>
#include <string.h>
#include "mem.h"
#include "spooler.h"
#include "ipc.h"
#include "sched.h"

TID Master, input_id, output_id;

void master_thread(void);
/*----------------------------------------------------------------------------+
| REQUIRES: nothing                                                           |
| MODIFIES: nothing                                                           |
| EFFECTS: starts the input spooler, output spooler, and command proccessors  |
|             as needed                                                       |
+----------------------------------------------------------------------------*/
