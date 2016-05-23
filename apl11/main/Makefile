# Makefile for main 

include ../include/makefile.common
CFLAGS += -I../include

OBJECTS = mainloop.o exit.o apl.o getinput.o history.o ascii_input.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	../include/apl.h

apl.o:	../include/patchlevel.h

getinput.o:	../include/config.h 

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) core

