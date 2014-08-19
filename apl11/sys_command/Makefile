# Makefile for syscom (system commands)

include ../include/makefile.common

OBJECTS = ex_syscom.o ex_prws.o ex_shell.o listdir.o ex_list.o 

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	apl.h

ex_prws.o:	char.h

ex_syscom.o:	opt_codes.h

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) core

