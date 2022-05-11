#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphe_adj_type.h"
#include "graphe_poids_type.h"
#include "util_adj.h"
#include "graphe.h"
int main()
{
  GRAPHE g1;
  
  g1=read_adj_mat("graphe_ex1.mat");
  printf("Graphe lu:\n");
  affiche_adj_mat(stdout,g1);
  dotty_adj_dot(g1);
  /* à faire:  fermeture transitive    */
  GRAPHE g2;                        
  g2=fermeture_transistive(g1);
  affiche_adj_mat(stdout,g2);
  dotty_adj_dot(g2);

  
  /* a faire: disjktra */
  /* GRAPHE_POIDS g3;  */
  /* g3=read_poids_mat("poids_ex1.mat"); */
  /* affiche_poids_mat(stdout,g3); */
  /* int *dist; */
  /* dotty_poids_dot(g3);  */
  /*  dist=dijkstra(g3,1);  */

  return 0;
}
