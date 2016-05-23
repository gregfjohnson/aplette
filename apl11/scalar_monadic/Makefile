# Makefile for scalar_monadic (monadic scalar functions)

include ../include/makefile.common
CFLAGS += -I../include

OBJECTS =  ex_abs.o ex_fac.o ex_not.o ex_sgn.o ex_ceil.o \
	ex_floor.o ex_pi.o ex_exp.o ex_loge.o ex_recip.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	../include/apl.h

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o 
