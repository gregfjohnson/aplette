# Makefile for struct_dyadic (structural dyadic operators)

include ../include/makefile.common

OBJECTS = ex_cat.o ex_drho.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	apl.h

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) core
