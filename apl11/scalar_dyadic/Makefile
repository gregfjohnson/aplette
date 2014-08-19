# Makefile for scalar_dyadic (dyadic scalar functions)

include ../include/makefile.common

OBJECTS = ex_cir.o ex_gt.o ex_min.o ex_ne.o ex_pwr.o ex_comb.o \
	ex_le.o ex_minus.o ex_sub.o ex_div.o ex_log.o \
	ex_mod.o ex_nor.o ex_add.o ex_eq.o ex_lt.o ex_mul.o ex_or.o \
	ex_and.o ex_ge.o ex_max.o ex_nand.o ex_plus.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	apl.h

.c.o:
	$(CC) $(CFLAGS) -c $<

