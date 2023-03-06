/* spooler.c */

#include <string.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include "sem.h"
#include "sched.h"
#include "mem.h"
#include "crit.h"
#include "fs.h"
#include "master.h"
#include "ipc.h"
#include "util.h"

int filect;
void output_spool(void)
/*----------------------------------------------------------------------------+
|  REQUIRES nothing                                                           |
|  MODIFIES file OUTPUT                                                       |
|  EFFECTS concatenates a file to the End of the OUTPUT file the name of the  |
|           file to be added on is sent in a message from the processor       |
+----------------------------------------------------------------------------*/
{
    char str[64], buf[1024];
    BUFFER *mybuf;
    int len;
    int fd, fd1;
    TID next;
    SID s;

    debug("output_spooler - entered");
    mybuf = b_get();
    debug("output_spooler - got buffer");
    for (;;)
    {
	debug("output_spooler - calling m_receive");
	m_receive(&next, mybuf);
	debug("output_spooler - received \n[%s] from [TID%d]\n",
	      (char *) mybuf, next);
	sprintf(str, "%-64s", (char *) mybuf);
	str[6] = '\0';
	s = s_open(FS_MAX);
	if ((s_wait(s)) == -1)
	    aprintf("output spooler - error waiting FS_MAX\n");
	fd = open("OUTPUT", O_WRONLY | O_APPEND | O_CREAT, 0666);
	if ((s_wait(s)) == -1)
	    aprintf("output spooler - error waiting FS_MAX\n");
	fd1 = open(str, O_RDONLY);
	while ((len = read(fd1, buf, 1024)) > 0)
	    write(fd, buf, len);
	close(fd);
	if ((s_signal(s)) == -1)
	    aprintf("output spooler - error waiting FS_MAX\n");
	close(fd1);
	if ((s_signal(s)) == -1)
	    aprintf("output spooler - error waiting FS_MAX\n");
	if ((s_close(s)) == -1)
	    aprintf("output spooler - error waiting FS_MAX\n");
    }
}



void input_spool(void)
/*----------------------------------------------------------------------------+
|  REQUIRES a INPUT FILE in current working directory                         |
|  MODIFIES IN--- files                                                       |
|  EFFECTS breaks up INPUT file into individual job files, sending a message  |
|          to master thread to start a processor for that job                 |
+----------------------------------------------------------------------------*/
{
    extern int filect;
    char str[80], name[24], filename[5], out[6];
    BUFFER *mbuf;
    TID next;
    SID s;
    int f1, f2;
    int i, x, j, index;
    char ch;
    int eof = 1;

    debug("Input_spooler - entered");
    filect = 0;
    mbuf = b_get();
    debug("Input_spooler - about to open INPUT");
    s = s_open(FS_MAX);
    if ((s_wait(s)) == -1)
	aprintf("output spooler - error waiting FS_MAX\n");
    if ((f1 = open("INPUT", O_RDONLY)) == NULL)
    {
	perror("input_spooler - error on file open f1");
	pod_exit(1);
    }
    debug("Input_spooler - entering while loop");
    while (eof > 0)
    {
	name[0] = '\0';
	str[0] = '\0';
	index = 0;
	while (((eof = read(f1, &ch, 1)) > 0) && (ch != '\n'))
	    str[index++] = ch;
	str[index++] = '\n';
	str[index] = '\0';
	if (eof > 0)
	{
	    if (strncmp(str, "//JOB", 5) == 0)
	    {
		sprintf(filename, "IN%03d", filect);
		sprintf(out, "OUT%03d", filect);
		if ((s_wait(s)) == -1)
		    aprintf("output spooler - error waiting FS_MAX\n");
		f2 = open(filename, O_WRONLY | O_CREAT, 0660);
		if ((x = strlen(str)) > 6)
		{
		    for (i = 6, j = 0; i < x; i++, j++)
			name[j] = str[i];
		}
                name[j] = '\0';
		str[0] = '\0';
		index = 0;
		while (((eof = read(f1, &ch, 1)) > 0) && (ch != '\n'))
		    str[index++] = ch;
		str[index++] = '\n';
		str[index] = '\0';
		while (strncmp(str, "/*", 2) != 0)
		{
		    write(f2, str, strlen(str));
		    str[0] = '\0';
		    index = 0;
		    while (((eof = read(f1, &ch, 1)) > 0) && (ch != '\n'))
			str[index++] = ch;
		    str[index++] = '\n';
		    str[index] = '\0';
		}
		close(f2);
		if ((s_signal(s)) == -1)
		    aprintf("output spooler - error waiting FS_MAX\n");
		debug("Input_spooler - about to send message");
		sprintf((char *) mbuf, "%-64s", "Create_Task");
		debug("[%s] is in buf, [%d] id of master", mbuf, Master);
		m_send(Master, mbuf);
		/* ipc_stat(); */
		debug("Input_spooler - after ipc stat");
		debug("Input_spooler - waiting for message");
		m_receive(&next, mbuf);
		debug("Input_spooler - received \n[%s] from [TID%d]\n", mbuf, next);
		/* ipc_stat(); */
		debug("Input_spooler - finished ipc_stat()");
		sprintf(str, "%-64s", (char *) mbuf);
		debug("Input_spooler - received [%s] \n", str);
		x = atoi(str);
		debug("Input_spooler - x = [%d]\n", x);
		sprintf((char *) mbuf, "%s%s", filename,name);
		debug("Input_spooler - sending \n[%s] ", mbuf);
		m_send(x, mbuf);
		debug("Input_spooler - sent \n[%s] to [TID%d]\n", mbuf, x);
		if (filect != 999)
		    ++filect;
		else
		    filect = 0;
		debug("Input_spooler - finished a pass");
	    }
	    else
		fprintf(stderr, "%s\n", "INPUT file with incorrect format");
	}
    }
    close(f1);
    if ((s_signal(s)) == -1)
	aprintf("output spooler - error waiting FS_MAX\n");
    if ((s_close(s)) == -1)
	aprintf("input spooler - error closing FS_MAX\n");
	b_release(mbuf);
    t_destroy();
}
