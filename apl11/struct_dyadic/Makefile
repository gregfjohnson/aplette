# Makefile for struct_dyadic (structural dyadic operators)

include ../include/makefile.common
CFLAGS += -I../include

OBJECTS = ex_cat.o ex_drho.o

all: Q.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	../include/apl.h

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) core
