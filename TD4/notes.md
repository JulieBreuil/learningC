# à retenir
- acceder à l'adresse d'une variable v
```
&v
```
- déclarer un pointeur
```
type *nom-du-pointeur
```
- la valeur stockée à l'adresse p
```
*p
```
- allocation dynamique, réservation d'un espace mémoire pour stocker un objet
```
char *malloc(int nombre-octets);
// fonction qui retourne un pointeur de type char * pointant vers //// un objet de taille nombre-octets octets
```
- libérer la mémoire allouée à p
```
free(p)
```


# introduction aux pointeurs
## Makefile
- $@ : nom de la cible
- $< : première dépendance
- $^ : liste des dépendances

## Questions
- Q36 : int Tab[5] est une déclaration de variable. un tableau n'est pas une Lvalue
- Q41 : l'écart est de 1

