#
# Makefile for OS4U
#
CC=/contrib/bin/gcc
CFLAGS= -g -O 
OFILES= \
	aprintf.o\
	crit.o\
        command.o\
	fs.o\
	ipc.o\
	list.o\
	main.o\
        master.o\
	mem.o\
	sched.o\
	sem.o\
        spooler.o\
	threads.o\
	util.o
#
all:	$(OFILES)
		$(CC) $(CFLAGS) -o os4u $(OFILES) ./tests/tg.o -llwp


clean:
		rm -f *.o os4u *.BAK core rundir/IN* rundir/OUT*

aprintf.o : aprintf.c aprintf.h crit.h maxprio.h 
command.o : command.c spooler.h sched.h list.h mem.h ipc.h sem.h master.h fs.h 
crit.o : crit.c crit.h maxprio.h 
fs.o : fs.c fs.h list.h sched.h crit.h maxprio.h mem.h sem.h util.h 
ipc.o : ipc.c ipc.h list.h mem.h sched.h sem.h util.h 
list.o : list.c debug.h list.h util.h 
main.o : main.c debug.h fs.h list.h sched.h mem.h threads.h maxprio.h tg.h util.h 
master.o : master.c spooler.h sched.h list.h mem.h ipc.h sem.h command.h fs.h 
mem.o : mem.c debug.h crit.h maxprio.h list.h mem.h sem.h util.h 
sched.o : sched.c debug.h fs.h list.h sched.h maxprio.h sem.h util.h 
sem.o : sem.c crit.h maxprio.h debug.h list.h sched.h sem.h util.h 
spooler.o : spooler.c sched.h list.h mem.h fs.h master.h spooler.h ipc.h sem.h 
threads.o : threads.c aprintf.h debug.h fs.h list.h sched.h maxprio.h mem.h \
  threads.h tg.h util.h 
util.o : util.c aprintf.h util.h 
