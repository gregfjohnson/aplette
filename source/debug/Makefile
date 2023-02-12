# Makefile for debug 

include ../include/makefile.common
CFLAGS += -I../include

OBJECTS = code_dump.o stack_dump.o mem_dump.o vars_dump.o parsedump.o

all: Q.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	../include/apl.h

# Things that depend on characters
code_dump.o:	../include/char.h ../include/opt_codes.h

mem_dump.o:	../include/memory.h

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) core

