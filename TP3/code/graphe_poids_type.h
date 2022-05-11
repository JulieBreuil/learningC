#ifndef GRAPHE_POIDS_TYPE_H
#define GRAPHE_POIDS_TYPE_H

struct graphe_poids {
  int nb_sommets;
  int **adj;
  int **poids;
  int *marque;
};
typedef struct graphe_poids GRAPHE_POIDS;
 
#endif
