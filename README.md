# learningC
## TD1
### Premier programme C
```c
#include <stdio.h>
int main()
{
    printf("hello World\n");
    return(0);
}
```
### Mon Premier Makefile

```makefile
all: hello

hello: hello.c
        gcc hello.c -o hello
        
clean:
        rm -f hello
```
Ce fichier Makefile, traduit en français veut dire :
* Lorsqu’on m’appelle (i.e. commande make), je dois réaliser la cible hello (ça c’est la première
ligne).
* Pour réaliser la cible hello, je dois avoir la cible hello.c (ligne 3, on dit : “hello dépend de
hello.c).
* De plus (ligne 4), si cette cible hello.c est plus récente que le hello que j’ai, je dois exécuter
la commande indiqué à la ligne suivante (après le caractère de tabulation) : gcc hello.c -o
hello.
* Enfin, pour réaliser la cible clean, je doit faire la commande rm -f hello.

Etapes pour excécuter un fichier:
* compiler le projet
```shell
make
```
* excécuter le projet
```shell
./hello
```

Un nouveau fichier Makefile en passant par le fichier objet .o

```makefile
all: hello

hello: hello.o
        gcc hello.o -o hello

hello.o: hello.c
        gcc -c hello.c -o hello.o

clean:
        rm -f hello
```


### Variables et types en C
#### Les variables en C
La notion de variable est très importante en programmation. Du point de vue sémantique, une
variable est une entité qui contient plusieurs information :
* Une variable possède un nom, on parle d’identifiant
* Une variable possède une valeur qui change au cours de l’exécution du programme
* Une variable possède un type qui caractérise la nature des valeurs qu’elle peut prendre.
```c
#include <stdio.h>
int main()
{
    int year;
    year=2018;
    printf("hello %d World\n",year);
    return(0);
}
```

#### Les types de base en C
En C, les variables doivent être déclarées avant d’être utilisées, on dit que C est un langage typé.
Les types de base en C sont désignés par des spécificateurs de type qui sont des mots clefs du
langages, il y en a essentiellement 3 :
* les caractères (char),
* les entiers (int, short, unsigned long)
* les flottants (nombres réels, float, double).

Une instruction composée d’un spécificateur de type et d’une liste d’identificateurs éventuel-
lement initialisés séparés par une virgule est une déclaration. Par exemple :
```c
int a; //declaration d’une variable a entiere, sans initialisation 
int b = 1, c; //declaration des variables b et c. b est initialise a 1
double x = 2.38e4; //declaration et initialisation de x de type double
char message[80]; // declaration d’une variable message
// de type ’tableau de 80 caracteres’ (cf next TD)
```

### Fichiers .h et .c
Les fichiers .h contiennent les en-têtes de fonction ainsi que les définitions de type.

Fichier hello.h
```c
int hello();
```

Fichier Makefile
```makefile
all: main

main: main.o hello.o
        gcc main.o hello.o -o main
        
hello.o: hello.c hello.h
        gcc -c hello.c -o hello.o
        
main.o: main.c hello.h
        gcc -c main.c -o main.o
        
clean:
        rm -f main *.o
```

Fichier main.c
```c
#include <stdio.h>
#include "hello.h"
int main()
{
    int erreur;
    erreur=hello();
    if (erreur!=0)
        printf("Error in hello\n");
    return(0);
}
```
Plusieurs remarques:
* les includes de notre dossier sont mis en guillemets, ceux de l'extérieur entre chevrons <>
