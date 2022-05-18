NAME		= serial
LIBS		= -lez430
SRC		= main.c
SRC_DIR		= src
######### CHANGE THIS VARIABLE ONLY #########
CRO_EZ_SRC	= ${PWD}/../
############################################
INC_DIR		= -I${CRO_EZ_SRC}/ez430-drivers/inc -I${CRO_EZ_SRC}/protothreads/protothreads
OUT_DIR		= bin
LIB_DIR		= ${CRO_EZ_SRC}/ez430-drivers/lib
OBJ_DIR		= .obj
DOC_DIR		= doc
DEP_DIR 	= .deps
OBJ		= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))
DEPS		= $(patsubst %.c,$(DEP_DIR)/%.d,$(SRC))
# Platform EZ430
CPU		= msp430f2274
CFLAGS		= -g -Wall -mmcu=${CPU} ${INC_DIR}
LDFLAGS		= -static -L${LIB_DIR} ${LIBS}
CC		= msp430-gcc
MAKEDEPEND	= ${CC} ${CFLAGS} -MM -MP -MT $@ -MF ${DEP_DIR}/$*.d

all: ${OUT_DIR}/${NAME}.elf ${OUT_DIR}/${NAME}.a43 ${OUT_DIR}/${NAME}.lst

download: all
	mspdebug rf2500 "prog ${OUT_DIR}/${NAME}.elf"

${OUT_DIR}/${NAME}.elf: ${OBJ}
	@mkdir -p ${OUT_DIR}
	${CC} -mmcu=${CPU} ${OBJ} ${LDFLAGS} -o $@

${OUT_DIR}/${NAME}.a43: ${OUT_DIR}/${NAME}.elf
	msp430-objcopy -O ihex $^ $@

${OUT_DIR}/${NAME}.lst: ${OUT_DIR}/${NAME}.elf
	msp430-objdump -dSt $^ >$@

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	@mkdir -p ${OBJ_DIR} ${DEP_DIR}
	${MAKEDEPEND} $<
	${CC} ${CFLAGS} -c $< -o $@

-include ${DEPS}

tar:	clean
	cd ..; tar cvf TP4-student-init.tar TP4-student-init

.PHONY: clean
clean:
	@rm -Rf ${OUT_DIR} ${OBJ_DIR} ${DEP_DIR} ${DOC_DIR} */*~

.PHONY: rebuild
rebuild: clean all

.PHONY: doc
doc:
	doxygen

