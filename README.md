# TD1
## Premier programme C
```c
#include <stdio.h>
int main()
{
    printf("hello World\n");
    return(0);
}
```
## Mon Premier Makefile

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


## Variables et types en C
### Les variables en C
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

### Les types de base en C
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

## Fichiers .h et .c
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

## Bibliothèque statique (static library) en C
Un fichier de bibliothèque statique en C est généralement simplement la concaténation d’un
certain nombre de fichiers objets que l’on regroupe dans une fichier .a grâce à la commande
ar. Par exemple pour créer une bibliothèque libpgcd.a à partir du fichier pgcd.o, la com-
mande est simplement la suivante (on ne s’attarde pas sur les options crs, vous pouvez faire
man pour en apprendre plus) :
```shell
ar -crs libpgcd.a pgcd.o
```

Les librairie en C sont par convention toutes préfixées par lib. Lorsque l’on utilise des librai-
ries dans un programme C, il faut indiquer à l’éditeur de lien où elles se trouvent. cela va se faire
grâce au flag -L. Donc pour utiliser la librairie libpgcd.a qui se trouve dans le répertoire
../libpgcd/, lors de l’édition de lien du fichier main.o par exemple, on exécutera la com-
mande :
```shell
gcc -Wall -L../libpgcd/ main.o -o main -lpgcd
```
Notez bien le -lpgcd en fin de ligne, si vous mettez ce flag avant, par exemple :
```shell
gcc -Wall -lpgcd -L../libpgcd/ main.o -o main
```
gcc ne trouvera pas la fonction pgcd(), c’est le seul flag de gcc pour lequel la position est
importante.

## Bibliothèque dynamique en C 

En général en C, le fichier pour une bibliothèque dynamique XXX s’appelle libXXX.so. On
a vu qu’elle s’appelait libXXX.a pour la version statique. Les bibliothèque dynamiques sont
beaucoup plus utilisées que les bibliothèques statiques : les tailles des binaires générés sont
beaucoup plus petites puisqu’ils n’incluent pas le code de la bibliothèque. Comme pour une
bibliothèque statique, on utilise pour cela la flag -lXXX en fin de ligne de la commande d’édi-
tion de lien pour indiquer au compilateur que notre programme a besoin d’utiliser la librairie
libXXX.so.

Pour les bibliothèques standard (https://fr.wikipedia.org/wiki/Bibliothèque_
standard_du_C) Le compilateur se débrouille tout seul pour trouver la librairie libXXX.so.
Par exemple pour la libraire mathématique qui contient un certain nombre de fonction utile
comme par exemple la fonction sqrt. Pour ces bibliothèques il n’y a pas besoin de flag par-
ticulier à l’édition de lien. mais on a toujours besoin des fichiers d’en-tête pour les fonctions
qu’on utilise, c’est la raison du #include <stdio.h> que vous retrouvez dans tous vos fi-
chier. Pour la librairie mathématique, on utilise #include <math.h>.
Vous pouvez vous même définir une bibliothèque, statique ou dynamique. Si on utilise une
bibliothèque statique, le code de la bibliothèque est rajouté dans votre binaire. Si on utilise une
bibliothèque dynamique, le code n’est pas inclus dans le binaire, mais il est chargé en mémoire
quand on charge le binaire en mémoire, ce qui permet de ne pas du duppliquer le code des
bibliothèques utilisées dans plusieurs exécutables.

# TD2
## Entrées/Sorties formatées : printf et scanf
### printf
Le principe des entrées/sorties formatées en C est le suivant :
* Le premier argument est une chaîne de caractères qui contient un certain nombre de
formats, par exemple %d pour un entier, %c pour un caractère.
* Les arguments suivants sont les valeurs qui vont être interprétées comme étant du type
spécifié par les formats, dans l’ordre de la chaîne de caractère.

L’instruction suivante :
```c
printf("Ascii[%d]=%c, en octal: %o en hexa: %x\n",65,65,65,65);
```

donnera comme affichage :

```
Ascii[65]=A, en octal: 101 en hexa: 41
```

Les différents formats sont les suivants:

format | type d’objet pointé | représentation de la donnée saisie
--- |---------------------| ---
%d | int                 | décimale signée
%hd | short int           | décimale signée
%ld | long int            | décimale signée
%u | unsigned int        | décimale non signée 
%hu | unsigned short int  | décimale non signée 
%lu | unsigned long int   | décimale non signée 
%o | int                 | octale
%ho | short int           | octale
%lo | long int | octale
%x | int | hexadécimale
%hx | short int | hexadécimale
%lx | long int | hexadécimale
%p | void * | pointeur : adresse en hexadecimal
%f | float | flottante virgule fixe
%lf | double | flottante virgule fixe
%Lf | long double | flottante virgule fixe
%e | float | flottante notation exponentielle
%le | double | flottante notation exponentielle
%Le | long double | flottante notation exponentielle
%g | float | flottante virgule fixe ou notation exponentielle
%lg | double | flottante virgule fixe ou notation exponentielle
%Lg | long double | flottante virgule fixe ou notation exponentielle
%c | char | caractère
%s | char* | chaîne de caractères

### scanf
Exemple d’utilisation de scanf :
```c
#include <stdio.h>
int main(){
    int i;
    printf("ENtrez un entier soous forme hexadécimale i=");
    scanf("%x",&i);
    printf("i = %d\n",i);

    return 0;
}
```

## Les fonctions en C
### Définition de fonctions en C
Exemple d'une fonction et de son appel
```c
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
```
Le mécanisme de **passage de paramètre** en C (on dit : passage de paramètre par valeur) doit
être bien compris :
* Une fonction communique des valeurs avec son environnement appelant à travers les
paramètres et le résultat.
* dans int factorielle(int n), n est le paramètre formel de la fonction. Il peut être
utilisé dans le corps de la fonction comme une variable locale.
* dans x=factorielle(10), 10 est le paramètre effectif utilisé lors de cet appel.
* En C, tout se passe lors de cette appel comme si on exécutait le corps de la fonction avec
la case mémoire pour n contenant une copie de la case mémoire contenant 10. On dit que les
paramètres sont passés par valeur.
* Lorsque l’appel est terminé, la case mémoire de n disparaît.
* __Donc__ : on peut modifier la valeur du paramètre formel n dans le corps de la fonction
mais cela ne modifiera pas la valeur du paramètre effectif (10)
* __Donc__ : Dans le code ci-dessus x n'est pas modifié, c'est y qui stocke le résultat de la fonction

### Portée des variables
Les variables manipulées dans un programme C n’ont pas toutes la même durée de vie. On
distingue deux catégories de variables.
* Les variables permanentes (ou statiques)
* Les variables temporaires

Chaque variable déclarée a une portée (ou durée de vie) qui est la portion de code dans laquelle
elle est connue. On peut déclarer des variables au début de chaque bloc (un bloc est le début
d’une fonction ou d’une portion de code entre accolade). La portée (ou durée de vie) de ces
variables est limitée au bloc.
Les blocs sont forcément imbriqués lexicalement, lors d’une utilisation d’une variable n, elle
peut avoir été déclarée deux fois dans la suite des blocs englobant. L’utilisation correspond à
celle de la première définition rencontrée lorsque l’on remonte dans les blocs (i.e. la dernière
effectuée temporellement).

## Retour sur les types de base et entrées/sorties
### stdin, stdout, Le buffer d’entrée de scanf
Par défaut, un programme C lit ses entrées sur un descripteur de ficher particulier qui s’appelle
stdin et écrit ses sorties sur stdout (et ses erreurs sur stderr. On verra comment on peut
rediriger les E/S vers d’autres fichiers, mais par défaut, stdin c’est le clavier et stdout c’est
l’écran (plus précisément : la console ou on exécute le programme exécutable)

scanf lit ses entrées dans un buffer (ou tampon en Français) qui est rempli lorsque l’on tape
un retour chariot après avec écrit ce que l’on voulait sur l’entrée standard stdin. Le problème
c’est que le caractère ’retour chariot’ est aussi mis dans le buffer, ce qui ne pose pas de problème
quand on lit des flottant, mais devient très très contre-intuitif quand on lit des caractères.

La solution est donc de ne jamais utiliser scanf pour lire des caractères. Utiliser les fonctions
getc et fgets pour cela

Code pour lire une chaine de caractères:
```c
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
```

### Les chaînes de caractères en C
En C une chaîne de caractères n’est pas un type de base : c’est un tableau de caractères terminé
par le caractère spécial ’\0’ (ou NULL : octet valant 0).

Pour l’instant, nous allons la déclarer comme un tableau de taille supérieure à la chaîne que
nous voulons y rentrer.

Par exemple, la déclaration :
```c
char chaine[80];
```
permettra de manipuler toutes les chaînes de moins de 79 caractères

# TD3
## Tableaux et boucle for
### Constructeurs de types
À partir des types prédéfinis du C (caractères, entiers, flottants), on peut créer de nouveaux
types, appelés types construits, qui permettent de représenter des ensembles de données orga-
nisées. Ces constructeurs de type permettent de définir :
* Les tableaux grâce à l’opérateur ’[’ ’]’
* Les structures grâce au mot-clé struct
* Deux autres types construits qui nous verrons plus tard
* Les unions avec le mot-clé union
* Les énumérations avec le mot-clé enum
* Tous les autres types construits par des combinaisons de ces constructeurs de type : ta-
bleaux de tableaux, tableau de structure, unions de structure etc.

Un tableau est (plus ou moins dans tous les langages) une collection d’objets de même type,
accessibles directement par un index. Les accès (lecture ou écriture) aux éléments de tableaux
se font avec l’opérateur ’crochet’, sauf pour l’initialisation lors de la déclaration. Par exemple
si l’on considère un tableau de 5 valeurs entière contenant les 5 premiers entiers pairs, on le
déclarera avec initialisation de la manière suivante en C :
```c
int entierPair5[5]={2,4,6,8,10};
```
Important : En C les tableaux commencent toujours à l’indice 0, on accède au contenu d’un
tableau tab à l’index i par l’opérateur crochet : tab[i]. Pour l’exemple ci-dessus on a donc
entierPair[0] qui vaut 2, entierPair[1] qui vaut 4 etc. Évidement le contenu des cases
d’un tableau peuvent être modifiées au cours d’un programme.

Important : Autre convention importante en C : les case successives d’un tableau sont rangées
de manière successive en mémoire, retenez cela pour l’instant nous l’utiliserons plus tard.

On peut définir des tableaux multidimensionnels. Exemple : matrice M d’entiers de 10 lignes
5 colonnes int M[10][5]. Par convention encore, les éléments de la matrice sont rangés par
ligne en mémoire.

### Instruction et expression en C
En C il est important de comprendre que toutes les expressions, en C, ont un résultat et (éven-
tuellement) un effet sur les variables en mémoire. Une instruction en revanche est une expres-
sion suivie d’un point-virgule, elle a donc un effet mais ne renvoi pas de résultat. 

Une des  différence du C avec les autres langages est que même les affectations ont un résultat, ce résultat c’est l’évaluation de la partie droite de l’affectation. Si on écrit :

```c
x=y=2
```

On aura bien x et y qui vaudront 2.

Plus formellement : Une expression est une suite de composants élémentaires syntaxiquement
correcte, par exemple : x = 0 ou bien (i >= 0) && (i < 10) qui produit :
* une action (modification possible de l’état des variables en mémoire)
* un résultat (valeur renvoyée par l’expression)

Une instruction est une expression suivie d’un point-virgule. Le point-virgule signifie en
quelque sorte “évaluer cette expression et oublier le résultat”. Plusieurs instructions peuvent
être rassemblées par des accolades { et } pour former une instruction composée (ou bloc) qui est
syntaxiquement équivalent à une instruction. Par exemple,
```c
{
    z = y / x;
    t = y % x;
}
```

| contexte                              | expression  | type/resultat | effet                       |
|---------------------------------------|-------------|---------------|-----------------------------|
| contexte                              | 8*8.6       | 68.8          | pas d'effet                 |
| q est de type float                   | q-2         | q-2           | pas d'effet                 |
| q est de type int                     | p= (q++) +1 | p=q+2         | la valeur de p est modifiée |
| z est de type int                     | z== 1?0:1   | z== 1?0:1     | pas d'effet                 |
| a est de type char, i est de type int | i=i+a       | i=i+a         | la valeur de i est modifiée |

### Boucle while

```c
i = 1;
while (i < 10)
{
    printf(" i = %d \n",i);
    i++;
}
```

### Boucle for
```c
for (i = 0; i < 10; i++)
    printf("\n i = %d",i);
```
Attention à la gestion des indices : dans l’exemple ci-dess us, à la fin de cette boucle, i vaudra
bien 10.

## Produit de matrice et entrées/sorties sur fichier
### Entrée/Sortie fichier
En C, Les accès à un fichier se font par l’intermédiaire d’un tampon (buffer) qui permet de
réduire le nombre d’accès au disque. Pour pouvoir manipuler un fichier, un programme a
besoin d’un certain nombre d’informations : adresse du tampon, position dans le fichier, mode
d’accès (lecture ou écriture) ... Ces informations sont rassemblées dans une structure dont le
type, FILE *, est défini dans stdio.h. Un objet de type FILE * est un flôt (stream).
Avant de lire ou d’écrire dans un fichier, on l’ouvre par la commande
```c
fich=fopen("nom-de-fichier","r")
```

Cette fonction dialogue avec le système d’exploitation et initialise un stream fich, qui sera ensuite utilisé lors de l’écriture ou de la lecture.
Après les traitements, on ferme le fichier grâce à la fonction fclose(fich).
Exemple : standard pour l’ouverture d’un fichier :
```c
FILE *fich;
fich=fopen("monFichier.txt","r");
if (!fich) fprintf(stderr,"Erreur d’ouverture : %s\n","monFichier.txt");
```

Un objet de type FILE * est quelquefois appelé un descripteur de fichier, c’est un entier désignant quel est le fichier manipulé. Trois descripteurs de fichier existent dans tous le programme C et peuvent être utilisés sans qu’il soit nécessaire de les ouvrir (à condition d’utiliser stdio.h) :
* stdin (standard input) : unité d’entrée (par défaut, le clavier, valeur du descripteur : 1) ;
* stdout (standard output) : unité de sortie (par défaut, l’écran, valeur du descripteur : 0) ;
* stderr (standard error) : unité d’affichage des messages d’erreur (par défaut, l’écran, valeur du descripteur : 2).

Une fois ouvert en lecture (paramètre "r") ou en écriture (paramètre "w"), on peut lire ou écrire dans un fichier avec les fonctions fprintf et fscanf exactement de la même manière que l’on lisait (au clavier) ou que l’on écrivait (à l’écran) avec les fonction printf ou scanf. En fait, printf("hello World!\n") est équivalent à fprintf(stdout,"hello World!\n"). la sortie standard est donc un fichier particulier.
   
Il existe d’autre fonctions pour lire ou écrire dans le fichiers lorsque les données ne sont pas  formatable avec le format de printf.

```c
if (!fichA)
{
    fprintf(stderr,"erreur d’ouverture du fichier %s\n",nomFichA);
    exit(-1);
}
```
La fonction fopen renvoi un entier (le descripteur de fichier) ou 0 lorsqu’il y a eu une erreur 1, donc
il y a un erreur si et seulement si fichA vaut 0. Dans tout les cas, on a bien if (!fichA) <=> if
(fichA==0)

## Instructions Conditionnelles : if et switch
### Instructions Conditionnelles
```c
if (expression-1 )
    instruction-1
else instruction-2
```
```c
switch (expression )
{case constante-1:
    liste d’instructions 1
    break;
case constante-2:
    liste d’instructions 2
    break;
case constante-3:
    liste d’instructions 3
    break;
default:
    liste d’instructions defaut
    break;
}
```
Attention, si l’on oublie les instructions break après une liste d’instruction, les instructions
du cas suivant seront exécutées jusqu’à ce qu’on rencontre un break. C’est une des spécificité du
langage C dont les motivations sont mystérieuses.

# TD4
## Introduction des pointeurs
Commençons par un rappel de l’organisation de la mémoire.
Nous l’avons représentée partant de l’adresse 0 (soit 0x00000000
en 32 bits) à la plus haute adresse possible (soit 0XFFFFFFFF en
32 bits).
### LValue
Toute variable manipulée dans un programme est stockée quelque part en mémoire. Pour retrouver une variable, il suffit donc de connaître l’adresse de l’octet où elle est stockée. C’est
le compilateur qui fait alors le lien entre l’identificateur d’une variable et son adresse en mémoire. Le langage C permet aussi de manipuler directement les cases mémoires à partir de
leur adresse, pour cela il introduit la notion de Lvalue.

On appelle Lvalue (modifiable left value) tout objet pouvant être placé à gauche d’un opérateur d’affectation. Une Lvalue est caractérisée par :
* son adresse, c’est-à-dire l’adresse mémoire à partir de laquelle l’objet est stocké ;
* sa valeur, c’est-à-dire ce qui est stocké à cette adresse.

Par exemple, une variable entière est une Lvalue (ex : i=1), un tableau ou une chaîne de caractère ne sont pas des Lvalue.
Une Lvalue est rangée à une adresse, on accède à cette adresse par l’opérateur adresse &,
l’adresse est en général rangée dans un entier (affiché en hexadécimal)
l’adresse d’une Lvalue n’est pas une Lvalue, c’est une constante (on ne peut pas la modifier)

### Pointeur
On déclare un pointeur par l’instruction :
```c
type *nom-du-pointeur;
```

où type est le type de l’objet pointé. Cette déclaration déclare un identificateur,
nom-du-pointeur, associé à un objet dont la valeur est l’adresse d’un autre objet de type
type.

L’identificateur nom-du-pointeur est donc en quelque sorte un identificateur d’adresse. Comme
pour n’importe quelle Lvalue, sa valeur est modifiable.

Par exemple Si on écrit :

```c
int i; //variable i de type int
int *p; //variable p de type
// pointeur vers int
i=3;
p=&i
```

p contient l’adresse de i (qui est par exemple la
valeur OxFFFF6C4d).

Si on regarde a l’adresse OxFFFF6C4d, on
trouve l’entier 3 rangé sur 4 octets
on y accède par opérateur unaire d’indirection * :
  *p désigne l’objet pointé par p
  c’est à dire la case mémoire à l’adresse
  OxFFFF6C4d qui contient la valeur 3.

#### Bilan

Soit le code suivant

```c
#include <stdio.h>

int main()
{
  int i = 3; //variable i de type int
  int *p; //variable p de type pointeur vers int
  p = &i;
  printf("i = %d \n",i);
  printf("&i = %p \n",&i);
  printf("*p = %d \n",*p);
  printf("p = %p \n",p);
}
```

variable | valeur
---|---
i | 3
&i | 0x7ffce92387dc
p | 0x7ffce92387dc
*p | 3

### Précision sur les Makefile
- $@ : nom de la cible
- $< : première dépendance
- $^ : liste des dépendances

## Arithmétique de pointeurs et parcours de tableau
### Arithmétique de pointeurs
La valeur d’un pointeur étant un entier (unsigned long int précisément), on peut lui appliquer un certain nombre d’opérateurs arithmétiques classiques. Les seules opérations arithmétiques valides sur les pointeurs sont :
* l’addition d’un entier à un pointeur. Le résultat est un pointeur de même type que le
pointeur de départ ;
* la soustraction d’un entier à un pointeur. Le résultat est un pointeur de même type que
le pointeur de départ ;
* la différence de deux pointeurs pointant tous deux vers des objets de même type. Le
résultat est un entier.
D’autre part ces opérations ne produisent pas le même résultat suivant le type de pointeur. Si
i est un entier et p est un pointeur sur un objet de type type, l’expression p + i désigne un
pointeur sur un objet de type type dont la valeur est égale à la valeur de p incrémentée de i * sizeof(type)

Exemple d'utilisation des pointeurs et des tableaux:
```c
#include <stdio.h>

#define N 5

int produit_scalaire(int A[N], int B[N])
{
  int i, res;
  int *p1, *p2;
  p1=A;
  p2=B;
  // p1 a pour valeur l'adresse de la première case du tableau A
  // p2 a pour valeur l'adresse de la première case du tableau B

  res=0;
  for (i=0;i<N;i++)
    {
      res += *p1 * *p2;
      p1++;
      p2++;
    }
  return res;
}

int main()
{
  int A[N]={1,1,1,1,1};
  int B[N]={1,1,1,1,1};

  printf("le produit scalaire vaut %d\n", produit_scalaire(A,B));

  return 0;
}
```

## Allocation dynamique
### Allocation dynamique
Le fait de réserver un espace-mémoire pour stocker un objet qui n’était pas prévu à la compilation s’appelle allocation dynamique. Beaucoup de langages l’implémentent avec le mot-clé
new.
En C, cela se fait par la fonction malloc de la librairie standard stdlib.h :
```c
char *malloc(int nombre-octets);
```
Cette fonction retourne un pointeur de type 
```c
char *
```
pointant vers un objet de taille  nombre-octets octets.
Pour initialiser des pointeurs vers des objets qui ne sont pas de type char, il faut convertir
le type de la sortie de la fonction malloc à l’aide d’un cast (conversion de type). L’argument
nombre-octets est souvent donné à l’aide de la fonction sizeof() qui renvoie le nombre
d’octets utilisés pour stocker un objet.
Pensez à tester le résultat de l’exécution de malloc, comme
tous les appels système, les erreurs sont simplement remontées dans le code du résultat, si ces appels échouent il
faut absolument le prendre en compte dans le programme
sous réserve de comportement incompréhensible. Rappelez vous aussi que allocation ne signifie pas initialisation à 0.
Enfin, lorsque la zone allouée n’est plus utile, on libère la
mémoire avec la fonction free.

### En pratique
0. Faire les imports nécessaires
```c
#include <stdlib.h>
```
1. Appeler malloc pour demander de la mémoire.

2. Vérifier la valeur retournée par malloc pour savoir si le système a bien réussi à allouer la mémoire.

3. Libérer la mémoire avec free une fois qu'on a fini d'utiliser la mémoire. Si on ne le fait pas, on s'expose à des fuites de mémoire, c'est-à-dire que votre programme risque de prendre beaucoup de mémoire alors qu'il n'a en réalité plus besoin de tout cet espace.

Exemple : allocation de 10 entiers. le schéma de droite
montre les différents emplacement des variables : la va-
riables p est (probablement) une variable locale, donc allouée dans la pile, alors que l’objet pointé par p est alloué
dans le tas.

```c
#include <stdlib.h>
[...]
int *p;
p=(int *)malloc(10*sizeof(int));
if (p==0)
  {
    fprintf(stderr,"Erreur d’allocation\n");
    exit(-1);
  }
for (i=0;i<10;i++)
  *(p+i)=0; //initialisation
[...]
free(p);
[...]
```

### Usage
Quand a-t-on besoin de l'allocation dynamique, alors ?

Le plus souvent, on s'en sert pour créer un tableau dont on ne connaît pas la taille avant l'exécution du programme.

```c
int main(int argc, char *argv[])
{
    int nombreDAmis = 0, i = 0;
    int* ageAmis = NULL; // Ce pointeur va servir de tableau après l'appel du malloc

    // On demande le nombre d'amis à l'utilisateur
    printf("Combien d'amis avez-vous ? ");
    scanf("%d", &nombreDAmis);

    if (nombreDAmis > 0) // Il faut qu'il ait au moins un ami (je le plains un peu sinon :p)
    {
        ageAmis = malloc(nombreDAmis * sizeof(int)); // On alloue de la mémoire pour le tableau
        if (ageAmis == NULL) // On vérifie si l'allocation a marché ou non
        {
            exit(0); // On arrête tout
        }

        // On demande l'âge des amis un à un
        for (i = 0 ; i < nombreDAmis ; i++)
        {
            printf("Quel age a l'ami numero %d ? ", i + 1);
            scanf("%d", &ageAmis[i]);
        }

        // On affiche les âges stockés un à un
        printf("\n\nVos amis ont les ages suivants :\n");
        for (i = 0 ; i < nombreDAmis ; i++)
        {
            printf("%d ans\n", ageAmis[i]);
        }

        // On libère la mémoire allouée avec malloc, on n'en a plus besoin
        free(ageAmis);
    }

    return 0;
}
```

## Pointeur et structure
### structure en C : struc
Une __structure__ est une suite finie d’objets de types différents. En C, contrairement aux tableaux,
les différents éléments d’une structure n’occupent pas nécessairement des zones contiguës
en mémoire. Chaque élément de la structure, appelé membre ou champ, est désigné par un
identificateur.

#### Déclaration de structure

Voici deux manières équivalentes de définir une variable z complexe comme une structure à deux champs. 
1. La structure est anonyme

```c
struct
{
    double reelle;
    double imaginaire;
} z;
```

2. On donne un label à la structure qui est un raccourci pour définir des variables avec ce type.
```c
struct complexe
{
    double reelle;
    double imaginaire;
};
```

#### Utilisation d’une variable de type de structure
```c
struct complexe z;
z.reelle = 10;
z.imaginaire = 20;
norme=sqrt(z.reelle*z.reelle+z.imaginaire*z.imaginaire);
```

En C, on associe souvent les structures et les pointeurs pour faire des listes chaînées.

### Structures auto-référencées
On a souvent besoin en C de modèles de structure dont un des membres est un pointeur vers
une structure de même modèle. Cette représentation permet en particulier de construire des listes
chaînées. Un élément de la liste chaînée est une structure appelée qui contient la valeur de
l’élément et un pointeur sur l’élément suivant. Le dernier élément pointe sur la liste vide NULL.

C’est la façon dont on implémente le type list en C. Une liste est une collection d’élément de
même type, mais contrairement aux tableaux, cette structure est dynamique, on peut rajouter
ou enlever des élément au cours de l’exécution du programme. La contrepartie est qu’on ne
peut pas accéder directement à chaque élément de la liste. En général on accède au premier
élément, à partir duquel on peut parcourir la liste pour trouver l’élément recherché. Ce mécanisme est implémenté par les liste chaînées constituées de l’association de structure et de
pointeurs.

#### Exemple
fichier liste.h
```c
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
```
fichier listeChainee.c
```c
#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

ELEMLIST *new_list(int val) //le paramètre de la fonction est la valeur d'un pointeur
{
    ELEMLIST *special_list = (ELEMLIST *)malloc(sizeof(ELEMLIST)); //*special_list est une valeur de type ELEMLIST
    (*special_list).val = val;
    return special_list; //special_list est une valeur de type pointeur
}


int main(int argc,char *argv[])
{
    int val = 5;
    ELEMLIST *ptr = new_list(val);
    printf("%d\n", (*ptr).val);
    return(0);
}
```
# TD5
## Arbres binaires en C
On commencera avec la définition de type
suivante pour un noeud d’un arbre binaire d’entier (un arbre étant simplement un pointeur vers un
noeud). Ici encore l’absence de fils est encodée par la valeur 0 pour le pointeur (on utilise plutôt la
macro NULL, définie dans <stdlib.h>).

### Exemple d'utilisation
fichier arbre_type.h
```c
struct model_noeud
{
    int val;
    struct model_noeud *filsGauche ;
    struct model_noeud *filsDroit ;
} ;
typedef struct model_noeud NOEUD;
typedef NOEUD *ARBRE;
```

fichier arbre.h
```c
#include "arbre_type.h"

ARBRE creerArbre(int val, ARBRE filsGauche, ARBRE filsDroit);
void afficheArbre(ARBRE unArbre);
```

fichier arbre.c
```c
#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"

ARBRE creerArbre(int val, ARBRE filsGauche, ARBRE filsDroit)
{
    NOEUD *unArbre = (NOEUD *)malloc(sizeof(NOEUD));
    (*unArbre).val = val;
    (*unArbre).filsGauche = filsGauche;
    (*unArbre).filsDroit = filsDroit;
    return unArbre;
}

void afficheArbre(ARBRE unArbre)
{
    printf("La valeur courante est %d \n",unArbre->val);
    if (unArbre->filsGauche != NULL)
    {
        afficheArbre(unArbre->filsGauche);
    }
    if (unArbre->filsDroit != NULL)
    {
        afficheArbre(unArbre->filsDroit);
    }
}
```

fichier main.c
```c
#include <stdio.h>
#include "arbre.h"

int main()
{
    int val = 3;
    int vol = 8;
    int vil = 9;
    ARBRE a = NULL;
    ARBRE b = NULL;
    ARBRE monArbre = creerArbre(val,a,b);
    ARBRE monArbre2 = creerArbre(vol,a,b);
    ARBRE monArbre3 = creerArbre(vil,monArbre,monArbre2);
    printf("Mon abre a pour valeur %d\n", monArbre->val);
    afficheArbre(monArbre3);
}
```

## Outil d’aide pour les fuites mémoire : Valgrind
valgrind est un outil de vérification de code à l’exécution. Le code est exécuté dans une machine
virtuelle qui vérifie les appels, adresses mémoires, etc. valgrind est essentiellement utilisé pour
découvrir tous les problèmes mémoires : “fuites mémoire” (memory leak : mémoire allouée mais non libérée) et accès en dehors des bornes des tableaux

valgrind est extrêmement simple d’utilisation, si votre programme se lance avec la commande :
```shell
monProg arg1 arg2
```
il suffit d’exécuter :
```shell
valgrind [option] monProg arg1 arg2
```
En pratique, il faut déjà excécuter votre programme normalement, puis utiliser valgrind.

## Outils de débugage : GDB
Nous allons étudier un outil fondamental du développement sous unix : gdb (et une interface
associée : nemiver ou ddd), debuggeur indispensable pour comprendre certaine erreurs.

Rajouter l’option -g à vos règles de Makefile qui produisent les fichiers .o. par
exemple
```makefile
arbre.o: arbre.c arbre.h arbre_type.h
    gcc -c -g arbre.c -o arbre.o
```
Recompilez votre programme et lancez la commande (en supposant que votre binaire exécutable
s’appelle main) :
```shell
gdb main
```
Vous devez avoir une invite gdb.
* Tapez la commande `break main`, puis `run`.
* Tapez alors la commande `layout src` qui vous permet de voir le code source en même temps.
* La commande `backtrace` permet à tout moment de connaître l’enchaînement d’appels de
fonctions successifs qui ont amené à cet instruction.
* La commande `step` avance d’une instruction C, c’est à dire qu’à l’appel d’une fonction, elle
entre dans le corps du code de la fonction.
* La commande `next` a le même comportement mais elle n’entre pas dans les fonctions appelées,
elle les exécute d’un seul coup.

gdb est un debugger symbolique, c’est-à-dire un utilitaire Unix permettant de contrôler le dé-
roulement de programmes C. Il permet (entre autres) de mettre des points d’arrêt dans un
programme, de visualiser l’état de ses variables, de calculer des expressions, d’appeler inter-
activement des fonctions, etc.

nemiver ou ddd sont des interfaces graphiques qui facilitent l’utilisation de gdb sous X-
Window, mais gdb ne nécessite aucun système de fenêtrage, il peut s’exécuter sur un simple
terminal shell (mode console). Il est indispensable de comprendre le fonctionnement en mode
gdb pour pouvoir utiliser les ddd.

Lorsque l’on lance gdb avec la commande gdb unexecutable.exe, gdb a chargé l’exécutable, 
il attend alors une commande gdb, comme par exemple run (pour exécuter le programme), break (pour mettre un point d’arrêt dans le programme), step (pour avancer d’une
instruction dans le programme), etc. Il y a donc une invite gdb.
Les points d’arrêt peuvent se positionner au début des fonctions (break main, par exemple),
ou à une certaine ligne (break 6, par exemple), ou lorsqu’une variable change de valeur
(watch i, par exemple).

Les commandes importantes (et leur raccourcit) à connaître pour utiliser gdb sont les suivantes :
* `r` est équivalent à `run`
* `b main` est équivalent à `break main`
* `b fonction` est équivalent à `break fonction`
* `p` var est équivalent à `print var`
* `d` var est équivalent à `display var`
* `s` est équivalent à `step`
* `n` est équivalent à `next`
* `c` est équivalent à `continue`
* La commande `run` peut prendre des arguments, le programme est alors exécuté avec les
arguments donnés
* La commande `print/x *( 0x000055555555529b)@10` permet d'afficher les 10 valeurs consécutives stockées en 
mémoire à partir de l’adresse 0x000055555555529b
* la commande `info` permet d’afficher des informations sur l’état du programme dans le
débugger. Par exemple `info b` liste les points d’arrêt.
* La commande `help` est l’aide en ligne de gdb

# TD 6
## Insertion dans une liste triée : deux moyens
Il existe deux moyens de définir une fonction f pour modifier une variable : 
* soit on affecte à la variable le résultat de la fonction f 
et dans ce cas la fonction elle-même ne modifie par la variable, par exemple `a=f(a);` ou `x=x+1;`

* soit on passe la variable en paramètre par référence à la fonction (et dans ce
cas, la fonction modifie la variable) : `inc(&x)` avec (par exemple) pour définition de inc :
```c
void inc(int *param)
{
    *param=*param+1;
}
```

Notons que pour les tableaux, on ne peut pas renvoyer un tableau comme résultat d’un fonction
puisqu’un tableau n’est pas une L-value. On est donc obligé, pour le modifier, de le passer en para-
mètre d’une fonction. Vous avez déjà fait ça dans le TP2 par exemple (passer un tableau en paramètre
et le modifier), et vous savez qu’on n’a pas besoin d’ajouter l’opérateur ’&’ devant le tableau passé en
paramètre. Effectivement, l’opérateur adresse (’&’) est implicite pour un tableau : le nom du tableau
indique l’adresse du premier élément.

Pour les listes par contre, on peut faire les deux, puisque les listes sont des pointeurs (qui sont des
L-values). On peut modifier une liste soit en la renvoyant comme résultat d’une fonction, soit en
passant en paramètre l’adresse de la liste (la liste étant elle-même un pointeur vers un ELEMLIST, on
passe donc un pointeur vers un pointeur vers un ELEMLIST)

### Passage par valeur

fichier liste_type.h
```c
#ifndef listeType_h_
#define listType_h_

struct model_elem {
  int elem ;
  struct model_elem* suivant;
};

typedef struct model_elem ELEMLISTE;

typedef ELEMLISTE *LISTE; 
 
#endif
```

fichier liste.h
```c
#ifndef list_h_
#define list_h_


void afficherListe(LISTE);	
LISTE AjouterListeTrie (LISTE, int);
void AjouterListeTrie2 (LISTE*, int);
void fusion (LISTE *pliste1, LISTE *pliste2);

#endif
```

fichier liste.c, méthode insertionListeTrie
```c
/*!
************************************************
* \brief ajouter un element dans une liste triee
*    et renvoyer la newListe liste
* \param liste adresse d'une liste 
* \param val un entier a ajouter à la liste triee
* \return Modifie La liste, insère l'élément inséré
* \return retourne la newListe liste
**************************************************/    
LISTE insertionListeTriee (LISTE liste1, int val)
{
    LISTE newListe = (LISTE)malloc(sizeof(ELEMLISTE));
    if (liste1 == NULL){
        newListe->elem=val;
        newListe->suivant=NULL;
        return newListe;
    }
    else
    {
        if(liste1->elem<val)
        {
            liste1->suivant= insertionListeTriee(liste1->suivant,val);
            return liste1;
        }
        else
        {
            newListe->elem=val;
            newListe->suivant=liste1;
            return newListe;
        }
    }
}
```

Quelques remarques:
* Le type LISTE est un pointeur vers ELEMLIST . Autrement dit, ELEMLIST est la valeur et LISTE est le pointeur
* un raccourci pour `(*newListe).elem` est `newListe->elem`

### Passage par référence
fichier liste.c, méthode insertionListeTrie2
```c
/*!
************************************************
* \brief ajouter un element dans une liste triee
* \param pliste adresse d'une liste 
* \param val un entier a ajouter à la liste triee
* \warning On passe un pointeur sur une liste (donc un pointeur
*   sur un pointeur sur un element)
* \return Modifie La liste, insère l'élément inséré
**************************************************/    
void insertionListeTriee2 (LISTE *pliste, int val)
{
    return;
}
```

Quelques remarques:
* pliste est un pointeur vers un objet de type LISTE donc pliste est un pointeur vers un pointeur qui pointe vers ELEMLIST
* Autrement dit, `*pliste` est de type `struct model_elem *` tandis que `pliste` est de type `struct model_elem **`
* Le premier paramètre de la fonction insertionListeTriee2 est de type `struct model_elem **`, il est parfois nécessaire
d'utiliser le caractère `&`, par exemple `insertionListeTriee2(&((*pliste)->suivant),val);`

## Le typedef
Pour comprendre le typedef :
* le mot clé typedef est suivit d’une déclaration qui a la même syntaxe qu’une déclaration
de variable, mais c’est une déclaration de type.
* On rappelle d’abord que l’opérateur * est associatif à droite (cf le poly ou google), on
`int **a` revient à `int (*(*a))` ;
* Il faut connaître les priorité des opérateurs. L’opérateur `[]` est plus prioritaire que
l’étoile dont la deuxième définition revient à :

`typedef int *p1d[10];` ⇔ `typedef int (*(p1d[10]));`
* Donc pour bien comprendre le type à partir de `typedef int (*(p1d[10]));`, on
fait :
  * `(*(p1d[10]))` est de type int
  * donc `(p1d[10]))` est de type pointeur vers un int
  * l’opérateur `[]` indique que ce qui est précède est un tableau plutot qu’un simple
  scalaire donc
  * `p1d` est de type tableau (de taille 10) de pointeurs vers int
* Pour l’autre `typedef int (*p1d)[10];`
  * `(*p1d)[10]` est de type int
  * `(*p1d)` est de type tableau (de taille 10) d’int
  * `p1d` est de type pointeur vers un tableau (de taille 10) d’int