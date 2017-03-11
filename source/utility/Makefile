# Makefile for utility 

include ../include/makefile.common
CFLAGS += -I../include

OBJECTS = floating.o iodone.o checksp.o fix.o topfix.o \
	errors.o file.o gamma.o signals.o optable.o \
	extend.o map.o scalar.o fappend.o fuzz.o readline.o

all: Q.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	../include/apl.h

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) core

