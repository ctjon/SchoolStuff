CC= /contrib/bin/gcc
CFLAGS= -O -g
OFILES= \
	list.o\
	tm.o\
        util.o
#
all:	$(OFILES)
		$(CC) $(CFLAGS) -o tm $(OFILES) 


clean:
		rm -f *.o tm *.BAK

list.o : list.c debug.h list.h util.h 
tm.o : tm.c list.h 
util.o : util.c util.h 
