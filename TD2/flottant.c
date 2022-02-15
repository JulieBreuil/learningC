#include <stdio.h>
int main(){
    float f;
    printf("Entrez un flottant f=");
    scanf("%f",&f);
    printf("f = %f\n",f);

    char chaine [80];
    printf("Entrez une chaîne: ");
    int c;
    while ( ((c = getchar() ) != '\n') && c != EOF){};
    fgets(chaine,80,stdin);
    printf("chaine lue: %s\n",chaine);

    return 0;
}