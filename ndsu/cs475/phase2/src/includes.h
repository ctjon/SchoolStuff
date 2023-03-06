#include <stdio.h>

#ifdef __MSDOS__
#include <alloc.h>
#endif



/*----------------------------------------------------------------------------+
|                                                                             |
| TEST SUITE DEFINES - set as required                                        |
|                                                                             |
+----------------------------------------------------------------------------*/

/* Module Tests to select from */
#define MEMTEST
#undef LISTTEST

/* Individual List Tests to select from */
#undef ADD_NODE
#undef INSERT_AT_FRONT
#undef INSERT_AT_END
#undef INSERT_AFTER_NTH
#undef INSERT_AFTER_ITEM
#undef DELETE_ITEM
#undef IS_IN_LIST
#undef LIST_ERROR
#undef REPLICATE_LIST
#undef CONCAT_LIST
