# Makefile for debug 

include ../include/makefile.common

OBJECTS = code_dump.o stack_dump.o mem_dump.o vars_dump.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	apl.h

# Things that depend on characters
code_dump.o:	char.h opt_codes.h

mem_dump.o:	memory.h

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) core

