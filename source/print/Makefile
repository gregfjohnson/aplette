# Makefile for print

include ../include/makefile.common
CFLAGS += -I../include

OBJECTS = print.o ex_hprint.o ex_print.o\
	fp_print.o lt_print.o c_overbar.o

all: Q.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	../include/apl.h

print.o:	../include/format.h

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o

