
#include <stdio.h>
int main(){
    for (int i=0; i<30; i++){
        int c = i*i;
        printf("Le carré de %4d est %4d\n",i,c);
        //le %4d permet l'alignement des chiffres sur la droite
    }
}