#include <stdio.h>

int factorielle(int n){
    int i, fact=1;

    for (i=1;i<n;i++){
        fact *= i;
    }
    return fact;
}
int main(){
    int x = 3;
    int y=factorielle(x);
    printf("!%d = %d\n",x,y);
}