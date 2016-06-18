# Makefile for APL11 

include	include/makefile.common

OBJECTS = debug/Q.o memory/Q.o parser/Q.o print/Q.o format/Q.o \
	quad_func/Q.o quad_var/Q.o data/Q.o ibeam/Q.o execute/Q.o \
	mixed_monadic/Q.o oper_monadic/Q.o scalar_monadic/Q.o \
	struct_monadic/Q.o \
	mixed_dyadic/Q.o oper_dyadic/Q.o scalar_dyadic/Q.o \
	struct_dyadic/Q.o \
	sys_command/Q.o userfunc/Q.o utility/Q.o work_space/Q.o main/Q.o 

all: apl11

apl11:	$(OBJECTS)
	$(CC) -o apl11 $(OBJECTS) $(LIBS)

$(OBJECTS):	include/apl.h

clean:	tidy
	rm -f apl11

tidy:
	rm -f $(OBJECTS) core parser/y.tab.* */*.o

debug/Q.o:	debug/*.c debug/*.h
	cd debug ; $(MAKE)

data/Q.o:	data/*.c
	cd data ; $(MAKE)

format/Q.o:	format/*.c
	cd format ; $(MAKE)

memory/Q.o:	memory/*.c
	cd memory ; $(MAKE)

parser/Q.o:	parser/*.c parser/apl.y parser/*.h
	cd parser ; $(MAKE)

print/Q.o:	print/*.c
	cd print ; $(MAKE)

ibeam/Q.o:	ibeam/*.c
	cd ibeam ; $(MAKE)

execute/Q.o:	execute/*.c
	cd execute ; $(MAKE)

quad_func/Q.o:	quad_func/*.c
	cd quad_func ; $(MAKE)

quad_var/Q.o:	quad_var/*.c
	cd quad_var ; $(MAKE)

mixed_monadic/Q.o:	mixed_monadic/*.c
	cd mixed_monadic ; $(MAKE)

oper_monadic/Q.o:	oper_monadic/*.c
	cd oper_monadic ; $(MAKE)

scalar_monadic/Q.o:	scalar_monadic/*.c
	cd scalar_monadic ; $(MAKE)

struct_monadic/Q.o:	struct_monadic/*.c
	cd struct_monadic ; $(MAKE)

mixed_dyadic/Q.o:	mixed_dyadic/*.c
	cd mixed_dyadic ; $(MAKE)

oper_dyadic/Q.o:	oper_dyadic/*.c
	cd oper_dyadic ; $(MAKE)

scalar_dyadic/Q.o:	scalar_dyadic/*.c
	cd scalar_dyadic ; $(MAKE)

struct_dyadic/Q.o:	struct_dyadic/*.c
	cd struct_dyadic ; $(MAKE)

sys_command/Q.o:	sys_command/*.c
	cd sys_command ; $(MAKE)

userfunc/Q.o:	userfunc/*.c
	cd userfunc ; $(MAKE)

utility/Q.o:	utility/*.c
	cd utility ; $(MAKE)

work_space/Q.o:	work_space/*.c
	cd work_space ; $(MAKE)

main/Q.o: main/*.c include/config.h
	cd main ; $(MAKE)

