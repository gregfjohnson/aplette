# Makefile for format conversions (ie downtackjot)

include ../include/makefile.common
CFLAGS += -I../include

OBJECTS = ex_mfmt.o fp_mfmt.o fp_digits.o fp2char.o\
	  ex_dfmt.o fp_dfmt.o fp2char_paded.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	../include/apl.h ../include/format.h

#Depends on char.h
fpt2char.o fp2char_paded.o fp_digits.o:	../include/char.h

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o
