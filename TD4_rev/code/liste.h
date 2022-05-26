#ifndef LIST_H
#define LIST_H

struct model_elem
{
    int val;
    struct model_elem *suivant;
};

typedef struct model_elem ELEMLIST;

ELEMLIST *new_list(int val);

#endif