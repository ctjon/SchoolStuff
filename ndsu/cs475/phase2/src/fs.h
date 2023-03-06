/* FS.H */

#ifndef __FSH__
#define __FSH__

#define MAX_OPEN_FILES 60	/* max number of open files      */
#define FS_MAX 500		/* max open files semaphore name */

#include "list.h"
#include "sched.h"

void fs_init(void);
/*-----------------------------------------------------------------------------+
| REQUIRES: nothing                                                            |
| MODIFIES: nothing                                                            |
| EFFECTS:  initializes the file system lists etc                              |
+-----------------------------------------------------------------------------*/

void fs_shutdown(void);
/*-----------------------------------------------------------------------------+
| REQUIRES: filesystem has been initialized                                    |
| MODIFIES: filesystem                                                         |
| EFFECTS:  closes streams and deletes file_list                               |
+-----------------------------------------------------------------------------*/

void dir(int output_stream);
/*-----------------------------------------------------------------------------+
| REQUIRES: nothing                                                            |
| MODIFIES: nothing                                                            |
| EFFECTS:  displays a list of files in the system's directory                 |
+-----------------------------------------------------------------------------*/

int create(char *file, int input_stream, int output_stream);
/*-----------------------------------------------------------------------------+
| REQUIRES: nothing                                                            |
| MODIFIES: file                                                               |
| EFFECTS:  creates file, adds it to the directory list, and appends text to   |
|           next TERMINAL_SYMBOL in file.  Returns 0 on success and -1         |
|           otherwise.  Note that if file already exists create() will fail.   |
|           On failure and error message will be produced on the output stream |
+-----------------------------------------------------------------------------*/

int del(char *file, int output_stream);
/*-----------------------------------------------------------------------------+
| REQUIRES: nothing                                                            |
| MODIFIES: file, file_list                                                    |
| EFFECTS:  deletes file from the file system.  Return 0 on success and -1 on  |
|           failure.  Failure will occur if file does not exist.  The file     |
|           will be deleted on the unix filesystem level as well.  On failure  |
|           an error message will be produced on the output stream.            |
+-----------------------------------------------------------------------------*/

int copy(char *file1, char *file2, int output_stream);
/*-----------------------------------------------------------------------------+
| REQUIRES: file1 exists and file2 is a valid file name                        |
| MODIFIES: file2, file_list                                                   |
| EFFECTS:  completely copies the contents of file1 into file2. Returns 0 on   |
|           success and -1 on failure.  Copy will fail if file2 already exists |
|           and produce an error message on the output stream.                 |
+-----------------------------------------------------------------------------*/

int cat(char *file, int output_stream);
/*-----------------------------------------------------------------------------+
| REQUIRES: nothing                                                            |
| MODIFIES: nothing                                                            |
| EFFECTS:  displays the contents of file if it exists and returns 0, else     |
|           cat displays and error message on the output stream and returns -1 |
+-----------------------------------------------------------------------------*/

#endif
