#include <stdio.h>

static int n=0;

int main(){

    int n = -1;

    printf("au début, n vaut %d\n",n);

    for (int i=0; i<10; i++){
        int n=10;
        n++;
        printf("à l'itération %d, n vaut %d\n",i,n);
    }

    printf("après la boucle, n vaut %d\n",n);

    return 0;
}