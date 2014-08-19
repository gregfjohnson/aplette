# Makefile for I-Beam functions

include ../include/makefile.common

OBJECTS = ex_dibm.o ex_mibm.o


Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	apl.h

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) core

