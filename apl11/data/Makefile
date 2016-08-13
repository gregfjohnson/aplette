# Makefile for data 

include	../include/makefile.common
CFLAGS += -I../include

OBJECTS = access.o dupdat.o getdata.o putdat.o top.o \
	bidx.o copy.o erase.o newdat.o s2vect.o \
	colapse.o fetch.o nlook.o size.o pop.o purge_name.o \
	data_iterator.o rbtree.o symtab.o

all: Q.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	../include/apl.h

# Things that depend on characters
fetch.o :	../include/char.h ../include/opt_codes.h

.c.o:
	$(CC) $(CFLAGS) -c $<

unit_test: data_iterator_unit_test

data_iterator_unit_test: data_iterator.c
	$(CC) $(CFLAGS) -DUNIT_TEST -o data_iterator_unit_test data_iterator.c

clean:
	rm -f $(OBJECTS) core data_iterator_unit_test

