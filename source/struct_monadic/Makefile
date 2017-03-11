# Makefile for struct_monadic 

include ../include/makefile.common
CFLAGS += -I../include

OBJECTS = ex_mrho.o ex_miot.o ex_rav.o

all: Q.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	../include/apl.h

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) core
