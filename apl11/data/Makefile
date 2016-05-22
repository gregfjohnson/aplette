# Makefile for data 

include	../include/makefile.common
CFLAGS += -I../include

OBJECTS = access.o dupdat.o getdata.o putdat.o top.o \
	bidx.o copy.o erase.o forloop.o newdat.o s2vect.o \
	colapse.o fetch.o nlook.o size.o pop.o purge_name.o \
	data_iterator.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	apl.h

# Things that depend on characters
fetch.o :	char.h opt_codes.h

.c.o:
	$(CC) $(CFLAGS) -c $<

unit_test: data_iterator_unit_test

data_iterator_unit_test: data_iterator.c
	$(CC) $(CFLAGS) -DUNIT_TEST -o data_iterator_unit_test data_iterator.c

clean:
	rm -f $(OBJECTS) core data_iterator_unit_test

