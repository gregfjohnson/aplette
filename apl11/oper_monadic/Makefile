# Makefile for oper_monadic (monadic operators)

include ../include/makefile.common
CFLAGS += -I../include

OBJECTS = ex_red.o ex_com.o ex_exd.o ex_scan.o 

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	../include/apl.h

ex_red.o ex_scan.o:	../include/opt_codes.h

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS)
