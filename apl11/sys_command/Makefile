# Makefile for syscom (system commands)

include ../include/makefile.common
CFLAGS += -I../include

OBJECTS = ex_syscom.o ex_prws.o ex_shell.o listdir.o ex_list.o 

all: Q.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	../include/apl.h

ex_prws.o:	../include/char.h

ex_syscom.o:	../include/opt_codes.h

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) core

