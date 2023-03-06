/* FS.C */

#include "fs.h"
#include "crit.h"
#include "mem.h"
#include "sem.h"
#include <stdio.h>
#include <time.h>
#include "util.h"
#include <sys/types.h>
#include <sys/fcntl.h>

#define FS_DIR 501
#define FS_CREATE 502
#define FS_DEL 503
#define FS_COPY 504
#define FS_CAT 505

#define MAX_LENGTH 100
#define TERMINAL_SYMBOL "//"

LIST *file_list;

typedef struct fs_node
{
    int fstatus;		/* open = 1 and closed = 0  */
    char fname[24];		/* name of the file         */
}       FS_NODE;


void fs_init(void)
/*-----------------------------------------------------------------------------+
| REQUIRES: nothing                                                            |
| MODIFIES: nothing                                                            |
| EFFECTS:  initializes the file system lists etc                              |
+-----------------------------------------------------------------------------*/
{
    extern LIST *file_list;

    file_list = create_list();
    s_create(FS_MAX, MAX_OPEN_FILES);
    s_create(FS_DIR, 1);
    s_create(FS_CREATE, 1);
    s_create(FS_DEL, 1);
    s_create(FS_COPY, 1);
    s_create(FS_CAT, 1);
    aprintf("OS4U File System Initialization Complete\n");
}

void fs_shutdown(void)
/*-----------------------------------------------------------------------------+
| REQUIRES: filesystem has been initialized                                    |
| MODIFIES: filesystem                                                         |
| EFFECTS:  closes streams and deletes file_list                               |
+-----------------------------------------------------------------------------*/
{
    extern LIST *file_list;
    FS_NODE *fs_node_ptr;

    while (!list_is_empty(file_list))
    {
	fs_node_ptr = node_item(file_list);
	aprintf("%s %s\n", "deleting", fs_node_ptr->fname);
	unlink(fs_node_ptr->fname);
	file_list = delete_node(file_list);
    }
    aprintf("%s\n", "OS4U - Destruction of Filesystem Complete");
}

void dir(int output_stream)
/*-----------------------------------------------------------------------------+
| REQUIRES: nothing                                                            |
| MODIFIES: nothing                                                            |
| EFFECTS:  displays a list of files in the system's directory                 |
+-----------------------------------------------------------------------------*/
{
    extern LIST *file_list;
    LIST *listcopy;
    FS_NODE *fs_node_ptr;
    SID sdir;
    char buf[MAX_LENGTH];

    sdir = s_open(FS_DIR);
    if ((s_wait(sdir)) == -1)
	aprintf("dir - error opening/downing FS_DIR\n");

    listcopy = file_list;
    sprintf(buf, "%s\n", "OS4U Directory Listing");
    write(output_stream, buf, strlen(buf));
    sprintf(buf, "%-24s %-6s\n",
	    "NAME", "STATUS");
    write(output_stream, buf, strlen(buf));
    while (!list_is_empty(listcopy))
    {
	fs_node_ptr = node_item(listcopy);
	sprintf(buf, "%-24s", fs_node_ptr->fname);
	write(output_stream, buf, strlen(buf));
	if (fs_node_ptr->fstatus == 1)
	    sprintf(buf, " %-6s\n", "open");
	else
	    sprintf(buf, " %-6s\n", "closed");
	write(output_stream, buf, strlen(buf));
	listcopy = next_node(listcopy);
    }
    if ((s_signal(sdir)) == -1)
	aprintf("dir - error upping FS_DIR\n");
    if ((s_close(sdir)) == -1)
	aprintf("dir - error closing FS_DIR\n");
}

int create(char *file, int input_stream, int output_stream)
/*-----------------------------------------------------------------------------+
| REQUIRES: nothing                                                            |
| MODIFIES: file                                                               |
| EFFECTS:  creates file, adds it to the directory list, and appends text to   |
|           next TERMINAL_SYMBOL in file.  Returns 0 on success and -1         |
|           otherwise.  Note that if file already exists create() will fail.   |
|           On failure and error message will be produced on the output stream |
+-----------------------------------------------------------------------------*/
{
    extern LIST *file_list;
    LIST *listcopy, *flist_copy;
    int new_file;
    FS_NODE *fs_node_ptr, *fptr, *node;
    SID screat, smax;
    int old_priority;
    int index;
    char buf[MAX_LENGTH];
    char ch;

    screat = s_open(FS_CREATE);
    if ((s_wait(screat)) == -1)
	aprintf("create - error opening/downing FS_CREATE\n");
    smax = s_open(FS_MAX);
    debug("create - entered create");


    /*
     * check to see if file already exists
     */
    listcopy = file_list;
    while (!list_is_empty(listcopy))
    {
	fs_node_ptr = node_item(listcopy);
	if (strncmp(fs_node_ptr->fname, file, 24) == 0)
	{
	    sprintf(buf, "%s %s\n", "create - file already exists -", file);
	    write(output_stream, buf, strlen(buf));

	    if ((s_signal(screat)) == -1)
		aprintf("create - error upping FS_CREATE\n");
	    if ((s_close(screat)) == -1)
		aprintf("create - error closing FS_CREATE\n");
	    return (-1);
	}
	listcopy = next_node(listcopy);
    }
    debug("create - file does not already exist");


    /*
     * file does not already exist so create it
     */
    if ((node = (FS_NODE *) malloc(sizeof(FS_NODE))) == NULL)
    {
	aprintf("%s\n", "create - insufficient memory available - exiting!");
	pod_exit(1);
    }
    else
    {
	old_priority = enter_crit();
	debug("create - file created successfully");
	node->fstatus = 0;
	strncpy(node->fname, file, 24);
	file_list = insert_at_end(file_list, sizeof(FS_NODE), node);
	debug("create - node created successfully");
	exit_crit(old_priority);
	if ((new_file = open(file, O_WRONLY | O_CREAT, 0660)) == -1)
	{
	    aprintf("create - new file open failure\n");
	    pod_exit(1);
	}
	else
	{
	    if ((s_wait(smax)) == -1)
		aprintf("create - error opening/downing FS_MAX\n");
	    flist_copy = file_list;
	    while (!list_is_empty(flist_copy))
	    {
		fptr = node_item(flist_copy);
		if (strncmp(fptr->fname, file, 24) == 0)
		    fptr->fstatus = 1;
		flist_copy = next_node(flist_copy);
	    }
	    debug("create - file opened successfully");


	    buf[0] = '\0';
	    while ((strncmp(buf, TERMINAL_SYMBOL, 2)) != 0)
	    {
		debug("create - no terminals encountered yet");
		index = 0;
		buf[0] = '\0';
		while (((read(input_stream, &ch, 1)) > 0) && (ch != '\n'))
		    buf[index++] = ch;
		buf[index++] = '\n';
		buf[index++] = '\0';
		debug("create - TID [%d] - line read from [%d] = [%s]",
		      t_myid(), input_stream, buf);
		if ((strncmp(buf, TERMINAL_SYMBOL, 2)) != 0)
		    write(new_file, buf, strlen(buf));
		debug("create - [%s] written to %s", buf, file);
	    }


	    debug("create - TERMINAL_SYMBOL encountered ");
	    close(new_file);
	    flist_copy = file_list;
	    while (!list_is_empty(flist_copy))
	    {
		fptr = node_item(flist_copy);
		if (strncmp(fptr->fname, file, 24) == 0)
		    fptr->fstatus = 0;
		flist_copy = next_node(flist_copy);
	    }
	    if ((s_signal(smax)) == -1)
		aprintf("create - error upping FS_MAX\n");
	    if ((s_close(smax)) == -1)
		aprintf("create - error closing FS_MAX\n");
	    debug("create - returning 0");

	    if ((s_signal(screat)) == -1)
		aprintf("create - error upping FS_CREATE\n");
	    if ((s_close(screat)) == -1)
		aprintf("create - error closing FS_CREATE\n");
	    return (0);
	}
    }
}

int del(char *file, int output_stream)
/*-----------------------------------------------------------------------------+
| REQUIRES: nothing                                                            |
| MODIFIES: file, file_list                                                    |
| EFFECTS:  deletes file from the file system.  Return 0 on success and -1 on  |
|           failure.  Failure will occur if file does not exist.  The file     |
|           will be deleted on the unix filesystem level as well.  On failure  |
|           an error message will be produced on the output stream.            |
+-----------------------------------------------------------------------------*/
{
    extern LIST *file_list;
    FS_NODE *fs_node_ptr;
    SID sdel;
    int old_priority;
    char buf[MAX_LENGTH];
    register int i;

    sdel = s_open(FS_DEL);
    if ((s_wait(sdel)) == -1)
	aprintf("del - error opening/downing FS_DEL\n");

    debug("del - entered for deletion of %s", file);
    debug("del - delete requested by TID %d", t_myid());


    old_priority = enter_crit();
    for (i = 1; i <= list_length(file_list); i++)
    {
	debug("del - searching for %s", file);
	fs_node_ptr = node_item(file_list);
	if (strncmp(fs_node_ptr->fname, file, 24) == 0)
	{
	    debug("del - found %s - proceeding", file);

	    /*
	     * physically remove the file delete the node from the fs list
	     */
	    unlink(file);
	    debug("del - physical deletion of %s completed", file);
	    file_list = delete_node(file_list);
	    debug("del - deleted fs_node from file list");

	    if ((s_signal(sdel)) == -1)
		aprintf("dir - error upping FS_DEL\n");
	    if ((s_close(sdel)) == -1)
		aprintf("dir - error closing FS_DEL\n");
	    exit_crit(old_priority);
	    return (0);
	}
	file_list = insert_at_end(file_list, sizeof(FS_NODE), fs_node_ptr);
	file_list = delete_node(file_list);
    }
    sprintf(buf, "%s %s\n", "del - file not found -", file);
    write(output_stream, buf, strlen(buf));
    debug("del - file not found - returning -1");
    if ((s_signal(sdel)) == -1)
	aprintf("dir - error upping FS_DEL\n");
    if ((s_close(sdel)) == -1)
	aprintf("dir - error closing FS_DEL\n");
    exit_crit(old_priority);
    return (-1);
}

int copy(char *file1, char *file2, int output_stream)
/*-----------------------------------------------------------------------------+
| REQUIRES: file1 exists and file2 is a valid file name                        |
| MODIFIES: file2, file_list                                                   |
| EFFECTS:  completely copies the contents of file1 into file2. Returns 0 on   |
|           success and -1 on failure.  Copy will fail if file2 already exists |
|           and produce an error message on the output stream.                 |
+-----------------------------------------------------------------------------*/
{
    extern LIST *file_list;
    LIST *listcopy, *flist_copy1, *flist_copy2;
    int file_stream_1, file_stream_2;
    char buf[MAX_LENGTH];
    FS_NODE *fs_node_ptr, *fptr1, *fptr2, *node;
    SID scopy, smax;
    int old_priority;
    int eof = 1;
    int index;
    char ch;

    scopy = s_open(FS_COPY);
    if ((s_wait(scopy)) == -1)
	aprintf("copy - error opening/downing FS_COPY\n");
    smax = s_open(FS_MAX);


    /*
     * check to see if file2 already exists
     */
    listcopy = file_list;
    while (!list_is_empty(listcopy))
    {


	fs_node_ptr = node_item(listcopy);
	if (strncmp(fs_node_ptr->fname, file2, 24) == 0)
	{
	    sprintf(buf, "%s %s\n", "copy - file already exists -", file2);
	    write(output_stream, buf, strlen(buf));
	    if ((s_signal(scopy)) == -1)
		aprintf("copy - error upping FS_COPY\n");
	    if ((s_close(scopy)) == -1)
		aprintf("copy - error closing FS_COPY\n");
	    if ((s_close(smax)) == -1)
		aprintf("copy - error closing FS_MAX\n");
	    return (-1);
	}
	listcopy = next_node(listcopy);
    }


    /*
     * check to see if file1 is a valid file and if so copy it
     */
    listcopy = file_list;
    while (!list_is_empty(listcopy))
    {
	fs_node_ptr = node_item(listcopy);
	if (strncmp(fs_node_ptr->fname, file1, 24) == 0)
	{
	    /*
	     * physically copy the file and add new file to list
	     */
	    if ((node = (FS_NODE *) malloc(sizeof(FS_NODE))) == NULL)
	    {
		aprintf("%s\n",
			"copy - insufficient memory available - exiting!");
		pod_exit(1);
	    }
	    else
	    {
		/*
		 * add the new file to the file_list
		 */
		old_priority = enter_crit();
		strncpy(node->fname, file2, 24);
		file_list = insert_at_end(file_list, sizeof(FS_NODE), node);
		exit_crit(old_priority);

		/*
		 * open the source file and update fstatus for that file
		 */
		if ((file_stream_1 = open(file1, O_RDONLY)) == -1)
		{
		    aprintf("copy - file1 open error\n");
		    pod_exit(1);
		}
		if ((s_wait(smax)) == -1)
		    aprintf("copy - error opening/downing FS_MAX\n");
		flist_copy1 = file_list;
		while (!list_is_empty(flist_copy1))
		{
		    fptr1 = node_item(flist_copy1);
		    if (strncmp(fptr1->fname, file2, 24) == 0)
			fptr1->fstatus = 1;
		    flist_copy1 = next_node(flist_copy1);
		}

		/*
		 * open the destination file and update fstatus for that file
		 */
		if ((file_stream_2 = open(file2, O_WRONLY | O_CREAT, 0660)) == -1)
		{
		    aprintf("copy - file2 open error\n");
		    pod_exit(1);
		}
		if ((s_wait(smax)) == -1)
		    aprintf("copy - error opening/downing FS_MAX\n");
		flist_copy2 = file_list;
		while (!list_is_empty(flist_copy2))
		{
		    fptr2 = node_item(flist_copy2);
		    if (strncmp(fptr2->fname, file2, 24) == 0)
			fptr2->fstatus = 1;
		    flist_copy2 = next_node(flist_copy2);
		}


		buf[0] = '\0';
		while (eof > 0)
		{
		    debug("copy - eof not encountered yet");
		    index = 0;
		    buf[0] = '\0';
		    while (((eof = read(file_stream_1, &ch, 1)) > 0) && (ch != '\n'))
			buf[index++] = ch;
		    buf[index++] = '\n';
		    buf[index++] = '\0';
		    if (eof <= 0)
			debug("copy - end of file found");
		    if (eof > 0)
		    {
			debug("copy - TID [%d] - line read from [%d] = [%s]",
			      t_myid(), file_stream_1, buf);
			write(file_stream_2, buf, strlen(buf));
			debug("copy - [%s] written to [%d]", buf, file_stream_2);
		    }
		}



		debug("copy - end of file %d", file_stream_1);
		close(file_stream_1);
		flist_copy1 = file_list;
		while (!list_is_empty(flist_copy1))
		{
		    fptr1 = node_item(flist_copy1);
		    if (strncmp(fptr1->fname, file2, 24) == 0)
			fptr1->fstatus = 0;
		    flist_copy1 = next_node(flist_copy1);
		}
		if ((s_signal(smax)) == -1)
		    aprintf("copy - error upping FS_MAX\n");


		close(file_stream_2);
		flist_copy2 = file_list;
		while (!list_is_empty(flist_copy2))
		{
		    fptr2 = node_item(flist_copy2);
		    if (strncmp(fptr2->fname, file2, 24) == 0)
			fptr2->fstatus = 0;
		    flist_copy2 = next_node(flist_copy2);
		}
		if ((s_signal(smax)) == -1)
		    aprintf("copy - error upping FS_MAX\n");

		if ((s_close(smax)) == -1)
		    aprintf("copy - error closing FS_MAX\n");

		if ((s_signal(scopy)) == -1)
		    aprintf("copy - error upping FS_COPY\n");
		if ((s_close(scopy)) == -1)
		    aprintf("copy - error closing FS_COPY\n");
		return (0);
	    }
	}
	listcopy = next_node(listcopy);
    }
    sprintf(buf, "copy - file not found - %s", file1);
    write(output_stream, buf, strlen(buf));
    if ((s_close(smax)) == -1)
	aprintf("copy - error closing FS_MAX\n");
    if ((s_signal(scopy)) == -1)
	aprintf("copy - error upping FS_COPY\n");
    if ((s_close(scopy)) == -1)
	aprintf("copy - error closing FS_COPY\n");
    return (-1);
}

int cat(char *file, int output_stream)
/*-----------------------------------------------------------------------------+
| REQUIRES: nothing                                                            |
| MODIFIES: nothing                                                            |
| EFFECTS:  displays the contents of file if it exists and returns 0, else     |
|           cat displays and error message on the output stream and returns -1 |
+-----------------------------------------------------------------------------*/
{
    extern LIST *file_list;
    LIST *listcopy, *flist_copy;
    int file_stream;
    FS_NODE *fs_node_ptr, *fptr;
    SID scat, smax;
    int eof = 1;
    int index = 0;
    char buf[MAX_LENGTH];
    char ch;

    scat = s_open(FS_CAT);
    if ((s_wait(scat)) == -1)
	aprintf("cat - error opening/downing FS_CAT\n");
    smax = s_open(FS_MAX);


    listcopy = file_list;
    while (!list_is_empty(listcopy))
    {
	fs_node_ptr = node_item(listcopy);
	if (strncmp(fs_node_ptr->fname, file, 24) == 0)
	{


	    if ((file_stream = open(file, O_RDONLY)) == -1)
	    {
		aprintf("cat - file open error\n");
		pod_exit(1);
	    }
	    flist_copy = file_list;
	    while (!list_is_empty(flist_copy))
	    {
		fptr = node_item(flist_copy);
		if (strncmp(fptr->fname, file, 24) == 0)
		    fptr->fstatus = 0;
		flist_copy = next_node(flist_copy);
	    }
	    if ((s_wait(smax)) == -1)
		aprintf("cat - error opening/downing FS_MAX\n");


	    buf[0] = '\0';
	    while (eof > 0)
	    {
		debug("cat - eof not encountered yet");
		index = 0;
		buf[0] = '\0';
		while (((eof = read(file_stream, &ch, 1)) > 0) && (ch != '\n'))
		    buf[index++] = ch;
		buf[index++] = '\n';
		buf[index++] = '\0';
		if (eof < 0)
		    aprintf("cat - read error has occured\n");
		if (eof == 0)
		    debug("cat - end of file found");
		if (eof > 0)
		{
		    debug("cat - TID [%d] - line read from [%s] = [%s]",
			  t_myid(), file, buf);
		    write(output_stream, buf, strlen(buf));
		    debug("cat - [%s] written to [%d]", buf, output_stream);
		}
	    }


	    close(file_stream);
	    flist_copy = file_list;
	    while (!list_is_empty(flist_copy))
	    {
		fptr = node_item(flist_copy);
		if (strncmp(fptr->fname, file, 24) == 0)
		    fptr->fstatus = 0;
		flist_copy = next_node(flist_copy);
	    }
	    if ((s_signal(smax)) == -1)
		aprintf("cat - error upping FS_MAX\n");
	    if ((s_close(smax)) == -1)
		aprintf("cat - error closing FS_MAX\n");


	    if ((s_signal(scat)) == -1)
		aprintf("cat - error upping FS_CAT\n");
	    if ((s_close(scat)) == -1)
		aprintf("cat - error closing FS_CAT\n");

	    return (0);
	}
	listcopy = next_node(listcopy);
    }
    sprintf(buf, "%s %s\n", "cat - file not found -", file);
    write(output_stream, buf, strlen(buf));
    if ((s_close(smax)) == -1)
	aprintf("cat - error closing FS_MAX\n");
    if ((s_signal(scat)) == -1)
	aprintf("cat - error upping FS_CAT\n");
    if ((s_close(scat)) == -1)
	aprintf("cat - error closing FS_CAT\n");
    return (-1);
}
