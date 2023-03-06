#
# Chris Tjon
# CS459
# 9 Feburary 1994
# Program 3 - Makefile for udp_ping
#

CC	= /contrib/bin/gcc
CFLAGS	= -O
OBJ	= udp_ping.o
MYLIB	= ../libnet/libnet.a
LIBS	= -lm -lresolv

all:	$(OBJ) 
		$(CC) $(OBJ) $(MYLIB) $(LIBS) -o udp_ping
clean:
	rm -f *.o udp_ping core *.BAK
