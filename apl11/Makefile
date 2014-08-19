# Makefile for APL11 

include	include/makefile.common

OBJECTS = debug/Q.o memory/Q.o parser/Q.o print/Q.o format/Q.o \
	quad_func/Q.o quad_var/Q.o data/Q.o ibeam/Q.o execute/Q.o \
	mixed_monadic/Q.o oper_monadic/Q.o scalar_monadic/Q.o \
	struct_monadic/Q.o \
	mixed_dyadic/Q.o oper_dyadic/Q.o scalar_dyadic/Q.o \
	struct_dyadic/Q.o \
	sys_command/Q.o userfunc/Q.o utility/Q.o work_space/Q.o main/Q.o 

apl11:	$(OBJECTS)
	$(CC) -o apl11 $(OBJECTS) $(LIBS)

$(OBJECTS):	include/apl.h

clean:	tidy
	rm -f apl11

tidy:
	rm -f $(OBJECTS) core parser/y.tab.* */*.o


file_io/Q.o:	file_io/*.c file_io/*.h
	cd file_io ; $(MAKE)

debug/Q.o:	debug/*.c debug/*.h
	cd debug ; $(MAKE)

data/Q.o:	data/*.c data/*.h
	cd data ; $(MAKE)

format/Q.o:	format/*.c format/*.h
	cd format ; $(MAKE)

memory/Q.o:	memory/*.c memory/*.h
	cd memory ; $(MAKE)

parser/Q.o:	parser/*.c parser/apl.y parser/*.h
	cd parser ; $(MAKE)

print/Q.o:	print/*.c print/*.h
	cd print ; $(MAKE)

ibeam/Q.o:	ibeam/*.c ibeam/*.h
	cd ibeam ; $(MAKE)

execute/Q.o:	execute/*.c execute/*.h
	cd execute ; $(MAKE)

quad_func/Q.o:	quad_func/*.c quad_func/*.h
	cd quad_func ; $(MAKE)

quad_var/Q.o:	quad_var/*.c quad_var/*.h
	cd quad_var ; $(MAKE)

mixed_monadic/Q.o:	mixed_monadic/*.c mixed_monadic/*.h
	cd mixed_monadic ; $(MAKE)

oper_monadic/Q.o:	oper_monadic/*.c oper_monadic/*.h
	cd oper_monadic ; $(MAKE)

scalar_monadic/Q.o:	scalar_monadic/*.c scalar_monadic/*.h
	cd scalar_monadic ; $(MAKE)

struct_monadic/Q.o:	struct_monadic/*.c struct_monadic/*.h
	cd struct_monadic ; $(MAKE)

mixed_dyadic/Q.o:	mixed_dyadic/*.c mixed_dyadic/*.h
	cd mixed_dyadic ; $(MAKE)

oper_dyadic/Q.o:	oper_dyadic/*.c oper_dyadic/*.h
	cd oper_dyadic ; $(MAKE)

scalar_dyadic/Q.o:	scalar_dyadic/*.c scalar_dyadic/*.h
	cd scalar_dyadic ; $(MAKE)

struct_dyadic/Q.o:	struct_dyadic/*.c struct_dyadic/*.h
	cd struct_dyadic ; $(MAKE)

sys_command/Q.o:	sys_command/*.c sys_command/*.h
	cd sys_command ; $(MAKE)

userfunc/Q.o:	userfunc/*.c userfunc/*.h
	cd userfunc ; $(MAKE)

utility/Q.o:	utility/*.c utility/*.h
	cd utility ; $(MAKE)

work_space/Q.o:	work_space/*.c work_space/*.h
	cd work_space ; $(MAKE)

main/Q.o:	main/*.c main/*.h include/config.h
	cd main ; $(MAKE)

