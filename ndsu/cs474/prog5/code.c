/*
 * CODE.C Written By: Chris Tjon For: CS474 Program 5 Due: 23 October 1992
 */

#include <stdio.h>
#include <signal.h>
#include <sgtty.h>

void abort(void);

struct sgttyb arg;
FILE *out;

void main(void)
{
    short save_flags;
    char ch;
    signal(14, abort);
    alarm(10);

    if ((out = fopen("code.out", "w")) == NULL)
	perror("error code.out open"), exit(1);
    if (gtty(2, &arg) != 0)
	perror("gtty failure"), exit(1);
    save_flags = arg.sg_flags;

    arg.sg_flags |= RAW;
    arg.sg_flags &= ~(CRMOD | ECHO);

    if (stty(1, &arg) != 0)
	perror("stty failure"), exit(1);
    arg.sg_flags = save_flags;

    while (ch != 004)
    {
	read(0, &ch, 1), alarm(10);
	printf("graphics-> %c  octal-> %o  hex-> %x\r\n\r\n", ch, ch, ch);
	fprintf(out, "graphics-> %c  octal-> %o  hex-> %x\r\n\r\n", ch, ch, ch);
    }
    if (stty(1, &arg) != 0)
	perror("stty failure"), exit(1);
    fclose(out);
}

void abort(void)
{
    stty(1, &arg);
    fprintf(stderr, "TIMEOUT, terminating\n");
    fprintf(out, "TIMEOUT, terminating\n");
    fclose(out);
    exit(0);
}
