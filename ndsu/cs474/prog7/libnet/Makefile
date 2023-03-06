#
# Makefile for networking library.
#
#	Use a single Makefile, even though the sources are in independent
#	directories for each system (BSD, System 5, Xenix) so that all
#	common files are in a single Makefile.
#

AR	= ar
LIBNET	= libnet.a
COMM_OBJ   = daemon.o dgsendrecv.o error.o hosterror.o \
		lock.o nspipe.o pty.o readline.o readn.o \
		rresvport.o rtt.o spipe.o \
		tcpopen.o timer.o ttymode.o ttyraw.o \
		udpopen.o writen.o
BSD_OBJ	   = idpopen.o sppopen.o sigchild.o
SUN_OBJ	   = sigchild.o
S5_OBJ	   = semaph.o
XENIX_OBJ  = semaph.o
RANLIB     = ranlib

all:
	make `systype.sh`

${COMM_OBJ}:	systype.h
${BSD_OBJ}:	systype.h
${S5_OBJ}:	systype.h
${XENIX_OBJ}:	systype.h

lib:	${OBJS}
	${AR} rv ${LIBNET} $?
	${RANLIB} ${LIBNET}
#This is added by roder
sun:
	make "CFLAGS = -O " \
		"OBJS = $(COMM_OBJ) $(SUN_OBJ)" "RANLIB = ranlib" lib

next:
	make "CFLAGS = -O -bsd" \
		"OBJS = $(COMM_OBJ) $(BSD_OBJ)" "RANLIB = ranlib" lib

bsd:
	make "CFLAGS = -O" \
		"OBJS = $(COMM_OBJ) $(BSD_OBJ)" "RANLIB = ranlib" lib

sys5:
	make "CFLAGS = -O -g -I/usr/netinclude" \
		"OBJS = $(COMM_OBJ) $(S5_OBJ)" "RANLIB = ls -l" lib

xenix:
	make "CFLAGS = -O -Ml -I/usr/include/exos" \
		"OBJS = $(COMM_OBJ) $(XENIX_OBJ)" "RANLIB = ls -l" lib

clean:
	rm -f *.o a.out core temp.* $(LIBNET)

