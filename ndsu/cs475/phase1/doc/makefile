#
# Example makefile
#
# Author: Blayne Puklich
# Created: 90Apr10 11:39
#

CC= gcc
PRINTER= nplains1
CFLAGS= -c
LFLAGS= -llwp
SRCS= main.c list.c tree.c
OBJS= main.o list.o tree.o

all: example

print:
	lpr -P$(PRINTER) Makefile $(SRCS)

clean:
	rm -f core $(OBJS) example

example: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o example

example.o: example.c example.h list.h tree.h
	$(CC) $(CFLAGS) example.c

list.o: list.c list.h
	$(CC) $(CFLAGS) list.c

tree.o: tree.c tree.h
	$(CC) $(CFLAGS) tree.c

