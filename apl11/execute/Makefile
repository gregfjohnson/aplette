# Makefile for execute 

include ../include/makefile.common

OBJECTS = ex_dscal.o ex_botch.o ex_cdyad.o ex_ddyad.o execute.o \
          ex_mdyad.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	apl.h

execute.o:	opt_codes.h

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) core

