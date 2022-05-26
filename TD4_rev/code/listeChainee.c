#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

ELEMLIST *new_list(int val)
{
    ELEMLIST *special_list = (ELEMLIST *)malloc(sizeof(ELEMLIST));
    (*special_list).val = val;
    return special_list;
}

int main(int argc,char *argv[])
{
    int val = 5;
    ELEMLIST *ptr = new_list(val);
    printf("%d\n", (*ptr).val);
    return(0);
}
