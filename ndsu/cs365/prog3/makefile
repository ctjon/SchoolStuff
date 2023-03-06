#Genmake v1.03 pl2  11/12/91  Copyright(c) 1990, 1991 by Kyle Saunders
CC= /bin/cc
CFLAGS= -O
OFILES= \
	line.o\
	doc.o\
	main.o\
	format.o
#
main:	$(OFILES)
		$(CC) $(CFLAGS) -o main $(OFILES)

line.o:	line.c\
		line.h
		$(CC) $(CFLAGS) -c line.c

doc.h:	\
		line.h
		touch doc.h

line.h:	
		touch line.h

doc.o:	doc.h\
		doc.c
		$(CC) $(CFLAGS) -c doc.c

main.o:	doc.h\
		main.c
		$(CC) $(CFLAGS) -c main.c

format.o:	doc.h\
		format.c
		$(CC) $(CFLAGS) -c format.c

