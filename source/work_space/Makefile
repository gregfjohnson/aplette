# Makefile for APL11 

include ../include/makefile.common
CFLAGS += -I../include

OBJECTS = ws_clear.o ws_load.o ws_save.o fdat.o

all: Q.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	../include/apl.h

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) core

