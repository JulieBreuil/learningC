#ifndef GRAPHE_LISTE_TYPE_H
#define GRAPHE_LISTE_TYPE_H

// déclaration des noms pour type récursif
struct sommet;
struct arc;

struct graphe_liste {
  int nb_sommets;
  struct sommet *sommets;
};
typedef struct graphe_liste GRAPHE_LISTE;

struct sommet {
  int num;
  struct arc *arcs;
  struct sommet *suivant;
};
typedef struct sommet SOMMET;

struct arc {
  struct sommet *voisin;
  struct arc *arc_suivant;
};

typedef struct arc ARC;


#endif
