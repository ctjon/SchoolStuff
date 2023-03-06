#
# Makefile for OS4U
#
CC=/contrib/bin/gcc
CFLAGS= -g -O
OFILES= \
	util.o\
	aprintf.o\
	crit.o\
	list.o\
	sem.o\
	mem.o\
	sched.o\
	threads.o\
	main.o
#
all:	$(OFILES)
		$(CC) $(CFLAGS) -o os4u $(OFILES) ./tests/tg.o -llwp


clean:
		rm -f *.o os4u *.BAK core

aprintf.o : aprintf.c debug.h aprintf.h crit.h maxprio.h 
crit.o : crit.c debug.h maxprio.h crit.h 
list.o : list.c debug.h list.h util.h 
main.o : main.c debug.h threads.h maxprio.h sched.h list.h util.h mem.h 
mem.o : mem.c debug.h util.h list.h mem.h sem.h 
sched.o : sched.c debug.h sched.h list.h util.h maxprio.h 
sem.o : sem.c debug.h maxprio.h util.h sched.h list.h sem.h crit.h 
threads.o : threads.c debug.h threads.h maxprio.h sched.h list.h util.h tg.h 
util.o : util.c util.h debug.h aprintf.h 
