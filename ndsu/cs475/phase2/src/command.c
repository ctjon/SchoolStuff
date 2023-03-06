/* command.c */
#include <stdio.h>
#include <string.h>
#include "spooler.h"
#include "mem.h"
#include "master.h"
#include "ipc.h"
#include "fs.h"
#include "sched.h"
#include "sem.h"
#include "util.h"




void processor(void)
/*----------------------------------------------------------------------------+
|  REQUIRES a job file                                                        |
|  MODIFIES a OUT--- file which it creates                                    |
|  EFFECTS processes a job file and informs output spooler of completion ofjob|
+----------------------------------------------------------------------------*/
{
    BUFFER *buf;
    char str[5], line[80], file1[24], file2[24], name[24], out[6];
    char error_buf[256];
    SID fentry;
    TID next;
    int i, j, f1, f2, index;
    int eof = 1;
    char ch;

    debug("processor - entered");
    buf = b_get();
    debug("processor - got buffer");
    strncpy(out, "OUTxxx", 6);
    debug("processor - calling m_receive");
    m_receive(&next, buf);
    debug("processor - received \n[%s] from [TID%d]\n", (char *) buf, next);
    sprintf(str, "%-64s", (char *) buf);
    out[3] = str[2];
    out[4] = str[3];
    out[5] = str[4];
    out[6] = '\0';
    index = 0;
    i = 5;
    while( str[i]!= ' ')
      name[index++] = str[i++];
    name[index] = '\0';
    debug("processor - str = [%s]\n", str);
    debug("processor - about to open files");
    fentry = s_open(FS_MAX);
    s_wait(fentry);
    s_wait(fentry);
    str[5] = '\0';
    f1 = open(str, O_RDONLY);
    f2 = open(out, O_WRONLY | O_CREAT, 0666);
    debug("processor - about to enter loop");
    while (eof > 0)
    {
	debug("processor - about to in loop");
	line[0] = '\0';
	index = 0;
	while (((eof = read(f1, &ch, 1)) > 0) && (ch != '\n'))
	    line[index++] = ch;
	line[index++] = '\n';
	line[index] = '\0';
	if (eof > 0)
	{
	    if (strncmp(line, "DIR", 3) == 0)
		dir(f2);
	    else if (strncmp(line, "DEL", 3) == 0)
	    {
		for (i = 0, j = 4; j < strlen(line) - 1; i++, j++)
		    file1[i] = line[j];
		file1[i] = '\0';
		del(file1, f2);
	    }
	    else if (strncmp(line, "CREATE", 6) == 0)
	    {
		for (i = 0, j = 7; j < strlen(line) - 1; i++, j++)
		    file1[i] = line[j];
		file1[i] = '\0';
		create(file1, f1, f2);
	    }
	    else if (strncmp(line, "CAT", 3) == 0)
	    {
		for (i = 0, j = 4; j < strlen(line) - 1; i++, j++)
		    file1[i] = line[j];
		file1[i] = '\0';
		cat(file1, f2);
	    }
	    else if (strncmp(line, "COPY", 4) == 0)
	    {
		i = 0, j = 5;
		while (line[j] != ' ')
		{
		    file1[i] = line[j];
		    i++;
		    j++;
		}
		file1[i] = '\0';
		j++;
		i = 0;
		while (line[j] != '\n')
		{
		    file2[i] = line[j];
		    i++;
		    j++;
		}
		file2[i] = '\0';
		debug("calling copy with [%s], [%s]", file1, file2);
		copy(file1, file2, f2);
	    }
	    else
	    {
		sprintf(error_buf, "Invalid Command -> %s\n", line);
		write(out, error_buf, strlen(error_buf));
	    }
	}
    }
    if (strlen(name) > 0)
    {
        name[strlen(name)-1] = '\0';
	aprintf("Job - %s is finished\n", name);
    }
    close(f1);
    close(f2);
    s_signal(fentry);
    s_signal(fentry);
    s_close(fentry);
    sprintf((char *) buf, "%-64s", out);
    m_send(output_id, buf);
    if (b_release(buf) == -1)
	aprintf("command - b_release failed\n");
    t_destroy();
}
