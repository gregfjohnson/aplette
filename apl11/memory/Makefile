# Makefile for memory 

include ../include/makefile.common
CFLAGS += -I../include

OBJECTS =  afreset.o alloc.o aplfree.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	../include/apl.h ../include/memory.h

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f Q.o $(OBJECTS) core
