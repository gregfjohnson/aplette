# Makefile for APL11 

include ../include/makefile.common

OBJECTS = ws_clear.o ws_load.o ws_save.o fdat.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	apl.h

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) core

