# Mon Mar  1 00:16:08 CST 1993
#  This has been updated to show you how to link in the test thread
#  groups.  --dmr


CC= gcc
CFLAGS= -g

ASSIGN1= /student/ndsu/88/roehrich/cs475/assign1/tlib/
TG= $(ASSIGN1)tg.o
TGH= $(ASSIGN1)tg.h


SRC= main.c sched.c thread.c aprintf.c
HDR= sched.h thread.h aprintf.h $(TGH)


OBJ= main.o sched.o thread.o aprintf.o


all:	$(OBJ)
	$(CC) $(CFLAGS) -o os $(OBJ) $(TG) -llwp

sched.o:	sched.h aprintf.h
thread.o:	thread.h sched.h aprintf.h
aprintf.o:	aprintf.h thread.h
