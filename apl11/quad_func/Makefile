# Makefile for quad_func (quad functions) 

include ../include/makefile.common
CFLAGS += -I../include

OBJECTS = eval_qlx.o ex_crp.o ex_float.o ex_open.o ex_seek.o iofname.o \
	ex_ap.o ex_dup.o ex_fork.o ex_pipe.o ex_signl.o \
	ex_chdir.o ex_exec.o ex_kill.o ex_rd.o ex_unlink.o \
	ex_close.o ex_exit.o ex_nc.o ex_read.o ex_wait.o \
	ex_create.o ex_fdef.o ex_nl.o ex_run.o ex_write.o ex_ex.o


Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	../include/apl.h

# Things that depend on characters
eval_qlx.o ex_nc.o ex_run.o ex_crp.o ex_exec.o ex_fdef.o \
ex_nl.o ex_rd.o ex_seek.o ex_write.o :	../include/char.h

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) core

