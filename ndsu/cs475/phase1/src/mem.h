/* MEM.H */

#ifndef __MEMH__
#define __MEMH__

#include <stdio.h>
#include "list.h"

#define MAXMEM 20
#define BUF_NAME 1

typedef LIST BUFFER;

void mmalloc(int num_blocks);
/*----------------------------------------------------------------------------+
| REQUIRES: nothing                                                           |
| MODIFIES: nothing                                                           |
| EFFECTS:  builds a list of num_blocks free buffers with 64 bytes each       |
+----------------------------------------------------------------------------*/

BUFFER *b_get(void);
/*----------------------------------------------------------------------------+
| REQUIRES: nothing                                                           |
| MODIFIES: nothing                                                           |
| EFFECTS:  returns a pointer to a 64 byte buffer if available, will block and|
|           wait for a buffer to become available                             |
+----------------------------------------------------------------------------*/

int b_release(BUFFER * b);
/*----------------------------------------------------------------------------+
| REQUIRES: buf_list is initialized and b has been previously allocated       |
| MODIFIES: b and buf_list                                                    |
| EFFECTS:  releases the buffer b making it available to other threads        |
+----------------------------------------------------------------------------*/

void unmmalloc(void);
/*----------------------------------------------------------------------------+
| REQUIRES: buf_list has been allocated by mmalloc()                          |
| MODIFIES: buf_list                                                          |
| EFFECTS:  returns all memory allocated by mmalloc to system                 |
+----------------------------------------------------------------------------*/

#endif				/* __MEMH__ */
