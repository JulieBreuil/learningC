#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphe_adj_type.h"
#include "util_adj.h"

/* Initialisation d'une matrice d'adjacence d'un graphe de nb_sommets (sans arcs) */
GRAPHE init_adj_mat(int nb_sommets)
{
  GRAPHE g;

  g.nb_sommets=nb_sommets;
  g.adj=(int **)malloc(nb_sommets*sizeof(int*));
  if (g.adj==(int **)NULL)
    {
      printf("Error: no more memory\n");
      exit(EXIT_FAILURE);
    }
  for (int i=0;i<nb_sommets;i++)
    {
      g.adj[i]=(int *)malloc(nb_sommets*sizeof(int));
      if (g.adj[i]==(int *)NULL)
	{
	  printf("Error: no more memory\n");
	  exit(EXIT_FAILURE);
	}
    }
  for  (int i=0;i<nb_sommets;i++)
    for (int j=0;j<nb_sommets;j++)
      g.adj[i][j]=0;

  return g;
}


/* lecture d'une matrice d'adjacence dans un fichier, creation du graphe correspondant */
GRAPHE read_adj_mat(char *nom_fich)
{
  int res;
  int nbRows,nbColumns,val;
  GRAPHE g;
  FILE *fich;

  fich=fopen(nom_fich,"r");
  if (fich==0)
    {
      printf("erreur opening %s\n",nom_fich);
      exit(EXIT_FAILURE);
    }
  
  fscanf(fich, "%d",&nbRows);
  fscanf(fich, "%d",&nbColumns);
  if (nbRows!=nbColumns)
    {
      printf("erreur matrice non carré\n");
      exit(EXIT_FAILURE);
    }
  g=init_adj_mat(nbRows);
  for (int i=0; i<nbRows; i++) 
    for (int j=0; j<nbRows; j++) 
     {
       res=fscanf(fich, "%d",&val);
       if (res==EOF)
         {
           fprintf(stderr,"Fin de ficher atteinte: manque des coefficients\n");
           exit(-1);
         }
       g.adj[i][j]=val;
     }
 return g;
}

/* affichage d'une matrice d'adjacence dans un fichier */
void affiche_adj_mat(FILE *fich,GRAPHE g)
{
  int nb_sommets;

  nb_sommets=g.nb_sommets;
  fprintf(fich,"%4d %4d",nb_sommets,nb_sommets);
  fprintf(fich,"     ");
  fprintf(fich,"     ");
  /*for (int j=0;j<nb_sommets;j++)
    {
      fprintf(stdout," %4d |",j+1);
    }
  */
  for  (int i=0;i<nb_sommets;i++)
    {
      fprintf(fich,"\n");
      for (int j=0;j<nb_sommets;j++)
	{
	  fprintf(fich," %4d ",g.adj[i][j]);
	}
    }	      
  fprintf(fich,"\n");
}  



/* affichage d'un graphe au format dot 
   a partir du format matrice d'adjacence */    
void print_adj_dot(FILE *fich,GRAPHE g)
{
  int  nb_sommets;

  nb_sommets=g.nb_sommets;
    
  fprintf(fich,"digraph G {\n");
  for (int i=0;i<nb_sommets;i++)
    {
      fprintf(fich,"\t \"noeud%d\";\n",i+1);
    }
  for (int i=0;i<nb_sommets;i++)
    {
      for (int j=0;j<nb_sommets;j++)
	{
	  if (g.adj[i][j] != 0)
	    {
	      fprintf(fich,"\t \"noeud%d\" -> \"noeud%d\";\n ",i+1,j+1);
	    }
	}
    }
  fprintf(fich,"}\n");
}


/* affichage (dans un fichier) d'un graphe au format dot 
   a partir du format matrice d'adjacence */    
void affiche_adj_dot(char *nom_fich,GRAPHE g)
{
  FILE *fich;

  fich=fopen(nom_fich,"w");
  if (fich==0)
    {
      printf("erreur opening %s\n",nom_fich);
      exit(EXIT_FAILURE);
    }
  print_adj_dot(fich,g);
  fclose(fich);
  fprintf(stdout,"Graphe written to %s\n",nom_fich);
}

/* affichage à l'écran avec dotty d'un graphe au format dot 
   a partir du format matrice d'adjacence */    
void dotty_adj_dot(GRAPHE g)
{
  char *nom="test_graphe.dot";
  char commande[20];
  
  affiche_adj_dot(nom,g);
  sprintf(commande,"dotty %s",nom);
  system(commande);
}


