#
# Makefile for simx16
#
CC=/contrib/bin/gcc
CFLAGS= -g -O
OFILES= \
	bus.o\
	debug.o\
	processor.o\
	get_bits.o\
	memory.o\
	loader.o\
	process_4bit.o\
	process_7bit.o\
	process_10bit.o\
	process_16bit.o\
        intrpt.o\
	main.o
#
all:	$(OFILES)
		$(CC) $(CFLAGS) -o simx16 $(OFILES) 


clean:
		rm -f *.o x16 *.BAK core

bus.o : bus.c bus.h memory.h debug.h 
debug.o : debug.c debug.h 
get_bits.o : get_bits.c 
loader.o : loader.c loader.h bus.h memory.h processor.h debug.h 
main.o : main.c loader.h memory.h bus.h 
memory.o : memory.c memory.h bus.h 
process_4bit.o : process_4bit.c processor.h bus.h debug.h 
processor.o : processor.c processor.h debug.h bus.h 
intrpt.o  : intrpt.c  
