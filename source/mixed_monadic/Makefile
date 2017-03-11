# Makefile for mixed_monadic functions

include ../include/makefile.common
CFLAGS += -I../include

OBJECTS = ex_menc.o ex_rand.o ex_mdom.o ex_execute.o ex_rev.o \
	ex_gdu.o ex_gdd.o gd.o

all : Q.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	../include/apl.h

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o
