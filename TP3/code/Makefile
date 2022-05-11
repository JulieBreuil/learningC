INCLUDES=graphe_adj_type.h  graphe_liste_type.h   util_adj.h \
         graphe.h   graphe_poids_type.h  util_poids.h
CFLAGS=-Wall -g

all: main

main: main.o util_adj.o graphe.o  util_poids.o 
	gcc main.o util_adj.o util_poids.o graphe.o -o main

main_sol: main_sol.o util_adj.o graphe_sol.o util_poids.o graphe_liste.o util_flot.o graphe_flot.o
	gcc main_sol.o util_adj.o util_poids.o graphe_liste.o graphe_sol.o util_flot.o graphe_flot.o -o main_sol

main_flot: main_flot.o util_flot.o graphe_flot.o
	gcc ${CFLAGS} main_flot.o util_flot.o graphe_flot.o -o main_flot

%.o: %.c $(INCLUDES)
	gcc ${CFLAGS} $< -c -o $@

clean:
	\rm -rf *.o main main_sol *~ test_*.dot

tarSol : clean
	cd ..; tar cvf TDGraphe-sol.tar  code/*

tar : clean
	cd ..; tar cvf TDGraphe.tar code/Makefile  \
	code/graphe.h code/graphe_adj_type.h code/graphe_ex1.dot \
	code/graphe_ex1.mat code/graphe_ex1_sol.dot code/graphe_liste.h	\
	code/graphe_liste_type.h code/graphe_poids_type.h code/main.c \
	code/poids_ex1.mat code/poids_test.mat code/util_adj.c code/util_adj.h \
	code/util_poids.c code/util_poids.h  code/util_flot.c code/util_flot.h \
	code/graphe_flot_type.h code/flot_ex1.mat  code/flot_ex2.mat 
