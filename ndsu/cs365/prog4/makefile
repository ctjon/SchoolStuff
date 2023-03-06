CC= cc
CFLAGS= -O 
OFILES= \
	dict.o\
	soundex.o\
	spellck.o\
	copyfile.o\
	tree.o
#
spellck:	$(OFILES)
		$(CC) $(CFLAGS) -o spellck $(OFILES)

dict.o:	dict.c\
		soundex.h\
		tree.h
		$(CC) $(CFLAGS) -c dict.c

dict.h:	\
		soundex.h\
		tree.h
		touch dict.h

soundex.o:	soundex.c\
		soundex.h
		$(CC) $(CFLAGS) -c soundex.c

soundex.h:	
		touch soundex.h

spellck.o:	dict.h\
		soundex.h\
		spellck.c\
		tree.h\
		copyfile.h
		$(CC) $(CFLAGS) -c spellck.c

copyfile.o:	copyfile.c
		$(CC) $(CFLAGS) -c copyfile.c

tree.o:	tree.c\
		treeintrn.h
		$(CC) $(CFLAGS) -c tree.c

tree.h:	
		touch tree.h

treeintrn.h:	
		touch treeintrn.h

copyfile.h:	
		touch copyfile.h

