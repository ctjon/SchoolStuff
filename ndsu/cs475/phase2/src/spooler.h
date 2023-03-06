/* spooler.h */

#include <string.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include "sched.h"
#include "mem.h"
#include "ipc.h"

void output_spool(void);
/*----------------------------------------------------------------------------+
|  REQUIRES nothing                                                           |
|  MODIFIES file OUTPUT                                                       |
|  EFFECTS concatenates a file to the End of the OUTPUT file the name of the  |
|           file to be added on is sent in a message from the processor       |
+----------------------------------------------------------------------------*/


void input_spool(void);
/*----------------------------------------------------------------------------+
|  REQUIRES a INPUT FILE in current working directory                         |
|  MODIFIES IN--- files                                                       |
|  EFFECTS breaks up INPUT file into individual job files, sending a message  |
|          to master thread to start a processor for that job                 |
+----------------------------------------------------------------------------*/
