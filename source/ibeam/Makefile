# Makefile for I-Beam functions

include ../include/makefile.common
CFLAGS += -I../include

OBJECTS = ex_dibm.o ex_mibm.o

all: Q.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	../include/apl.h

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) core

