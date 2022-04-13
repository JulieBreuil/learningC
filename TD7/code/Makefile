CC=gcc
CFLAGS=-Wall 

#TARGET = tcp_client1
TARGET = tcp_client tcp_client1 tcp_client2 tcp_server tcp_server1 tcp_server2 
SRC=$(TARGET:=.c)
OBJ=$(SRC:.c=.o)

all: ${TARGET} #tar tar-sol


%.o: %.c
	${CC} -c ${CFLAGS} $< 


%: %.o
	${CC} $< -o $@



clean:
	-rm -f *.o ${BIN} *~ tcp_client tcp_client1 tcp_client2 tcp_server tcp_server1 tcp_server2 


tar:
	cd ..; tar cvf TD7-code.tar code/Makefile code/tcp_client1.c

tar-sol: clean
	cd ..; tar cvf TD7-sol.tar code/*

