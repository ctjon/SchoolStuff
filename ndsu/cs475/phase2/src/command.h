/* command.c */
#include <stdio.h>
#include <string.h>
#include "mem.h"
#include "spooler.h"
#include "ipc.h"
#include "fs.h"
#include "sched.h"





void processor(void);
/*----------------------------------------------------------------------------+
|  REQUIRES a job file                                                        |
|  MODIFIES a OUT--- file which it creates                                    |
|  EFFECTS processes a job file and informs output spooler of completion ofjob|
+----------------------------------------------------------------------------*/
