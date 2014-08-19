# Makefile for struct_monadic 

include ../include/makefile.common

OBJECTS = ex_mrho.o ex_miot.o ex_rav.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	apl.h

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) core
