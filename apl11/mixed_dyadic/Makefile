# Makefile for mixed_dyadic (dyadic mixed functions)

include ../include/makefile.common

OBJECTS = ex_base.o ex_index.o ex_tak_drp.o ex_ddom.o ex_diot.o \
          ex_rep.o ex_trn.o ex_deal.o ex_eps.o ex_rot.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	apl.h

ex_base.o ex_index.o:	opt_codes.h

.c.o:
	$(CC) $(CFLAGS) -c $<

