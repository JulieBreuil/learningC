#ifndef GRAPHE_FLOT_TYPE_H
#define GRAPHE_FLOT_TYPE_H

struct graphe_flot {
  int nb_sommets;
  int **adj;
  int **poids;
  int **flot;
  int *marque;
};
typedef struct graphe_flot GRAPHE_FLOT;
 
#endif
