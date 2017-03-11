# Makefile for mixed_dyadic (dyadic mixed functions)

include ../include/makefile.common
CFLAGS += -I../include

OBJECTS = ex_base.o ex_index.o ex_tak_drp.o ex_ddom.o ex_diot.o \
          ex_rep.o ex_trn.o ex_deal.o ex_eps.o ex_rot.o

all: Q.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	../include/apl.h

ex_base.o ex_index.o:	../include/opt_codes.h

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) core Q.o
