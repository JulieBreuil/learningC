#include <stdio.h>

int multi(){
    int rep=0;
    while (rep!=15){
        int i;
        printf("3*5=");
        scanf("%d",&i);
        rep=i;
    }
    return rep;
}

int main(){
    int res=multi();
    printf("Le resultat est %d\n",res);
}
