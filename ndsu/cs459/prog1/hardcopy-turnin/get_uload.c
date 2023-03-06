/*
 * Chris Tjon
 * CS459
 * Program1
 * get_uload.c
 * 26 Jan 94
 */

#include <X11/Xos.h>
#include <X11/Intrinsic.h>
#include <stdio.h>
#include <math.h>

static xload_error(void);
static int     lastNullCpu;
static int     lastClock;

int spawn(void);
void InitLoadPoint(void);
void GetLoadPoint(Widget w, caddr_t closure, caddr_t call_data);


void InitLoadPoint(void) {}

void GetLoadPoint(Widget w, caddr_t closure, caddr_t call_data)
{
	extern char *System;
	char buf1[80], buf2[80];
	FILE *fp;

	if (spawn() == 0)
		if ((execlp("rsh", System, "uptime",0L)) == -1)
			perror("execlp failed"),exit(1);
	fp = fdopen(0,"r"); /* open stdin */

	/* stupid little loop to pull the number of users out of the uptime line */
	fscanf(fp,"%s",buf1);
	while (strncmp(buf1,"user",4) != 0)
	{
		strcpy(buf2,buf1);
		fscanf(fp,"%s",buf1);
	}
#ifdef DEBUG
	printf("actual users on this pass = [%s]\n",buf2);
#endif

	*(double *)call_data = (atoi(buf2) / 10);
	return;
}

int spawn(void)
{
	int fd[2], pid;
	if (pipe(fd) == -1)
		perror("pipe failed"),exit(1);
	if ((pid = fork()) == -1)
		perror("fork failed"),exit(1);
	if (pid == 0)
	{
		close(1);
		dup(fd[1]);
	}
	else
	{
		close(0);
		dup(fd[0]);
	}
	close(fd[1]);
	close(fd[0]);
	return pid;
}
