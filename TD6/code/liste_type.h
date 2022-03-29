#ifndef listeType_h_
#define listType_h_

struct model_elem {
  int elem ;
  struct model_elem* suivant;
};

typedef struct model_elem ELEMLISTE;

typedef ELEMLISTE *LISTE;
//le type LISTE est un pointeur vers le type ELEMLIST
 
#endif
