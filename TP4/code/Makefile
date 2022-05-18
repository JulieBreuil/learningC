

SUBDIRS = ez430-drivers protothreads   TP4-student-init  #TP4-prof-radio-decode TP4-student-sol

all:
	@for DIR in $(SUBDIRS); do \
		(cd $$DIR && $(MAKE)); \
        done

tar-init: 
	tar cvf TCMSP-init.tar ../code/ez430-drivers ../code/TP4-student-init ../code/protothreads ../code/Makefile

.PHONY: all clean TDs tar-init

clean:
	\rm -f *~ *.tar
	@for DIR in $(SUBDIRS); do \
		(cd $$DIR && $(MAKE) clean && rm -f *.tar); \
        done

