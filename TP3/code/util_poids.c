#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphe_poids_type.h"
#include "util_poids.h"


/* Initialisation d'un graphe valué (type GRAPHE_POIDS)  de nb_sommets (sans arcs) */
GRAPHE_POIDS init_poids_mat(int nb_sommets)
{
  GRAPHE_POIDS g;

  g.nb_sommets=nb_sommets;
  g.adj=(int **)malloc(nb_sommets*sizeof(int*));
  g.poids=(int **)malloc(nb_sommets*sizeof(int*));
  if ((g.adj==(int **)NULL)||(g.poids==(int **)NULL))
    {
      printf("Error: no more memory\n");
      exit(EXIT_FAILURE);
    }
  for (int i=0;i<nb_sommets;i++)
    {
      g.adj[i]=(int *)malloc(nb_sommets*sizeof(int));
      g.poids[i]=(int *)malloc(nb_sommets*sizeof(int));
      if ((g.adj[i]==(int *)NULL)||(g.adj[i]==(int *)NULL))
	{
	  printf("Error: no more memory\n");
	  exit(EXIT_FAILURE);
	}
    }
  for  (int i=0;i<nb_sommets;i++)
    for (int j=0;j<nb_sommets;j++)
      {
	g.adj[i][j]=0;
	g.poids[i][j]=0;
      }
  g.marque=(int *)malloc(nb_sommets*sizeof(int));
  if  (g.marque==(int *)NULL)
    {
      printf("Error: no more memory\n");
      exit(EXIT_FAILURE);
    }
  for  (int i=0;i<nb_sommets;i++)
    g.marque[i]=0;
  
  return g;
}

/* lecture de deux matrices (adjacence et poids) dans un fichier, creation du graphe correspondant */
GRAPHE_POIDS read_poids_mat(char *nom_fich)
{
  int res;
  int nbRows,nbColumns,nbRows2,nbColumns2,val;
  GRAPHE_POIDS g;
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
  g=init_poids_mat(nbRows);
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
  fscanf(fich, "%d",&nbRows2);
  fscanf(fich, "%d",&nbColumns2);
  if ((nbRows2!=nbRows) || (nbColumns2!=nbRows))
    {
      printf("erreur matrice de poids non conforme\n");
      exit(EXIT_FAILURE);
    }
  for (int i=0; i<nbRows; i++) 
    for (int j=0; j<nbRows; j++) 
     {
       res=fscanf(fich, "%d",&val);
       if (res==EOF)
         {
           fprintf(stderr,"Fin de ficher atteinte: manque des coefficients\n");
           exit(-1);
         }
       g.poids[i][j]=val;
     }
 return g;
}

/* affichage des deux matrices (adjacence et poids) d'un graphe valué
  dans un fichier */
void affiche_poids_mat(FILE *fich,GRAPHE_POIDS g)
{
  int nb_sommets;

  nb_sommets=g.nb_sommets;
  fprintf(fich,"%4d %4d",nb_sommets,nb_sommets);
  fprintf(fich,"     ");
  fprintf(fich,"     ");
  for  (int i=0;i<nb_sommets;i++)
    {
      fprintf(fich,"\n");
      for (int j=0;j<nb_sommets;j++)
	{
	  fprintf(fich," %4d ",g.adj[i][j]);
	}
    }	      
  fprintf(fich,"\n");
  fprintf(fich,"%4d %4d",nb_sommets,nb_sommets);
  fprintf(fich,"     ");
  fprintf(fich,"     ");
  for  (int i=0;i<nb_sommets;i++)
    {
      fprintf(fich,"\n");
      for (int j=0;j<nb_sommets;j++)
	{
	  fprintf(fich," %4d ",g.poids[i][j]);
	}
    }	      
  fprintf(fich,"\n");
}  



/* affichage d'un graphe valué au format dot 
   a partir du type GRAPHE_POIDS */    
void print_poids_dot(FILE *fich,GRAPHE_POIDS g)
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
	      fprintf(fich,"\t \"noeud%d\" -> \"noeud%d\" ",i+1,j+1);
	      fprintf(fich,"[ label=%d ];\n",g.poids[i][j]);
	    }
	}
    }
  fprintf(fich,"}\n");
}
  

/* affichage (dans un fichier) d'un graphe au format dot 
   a partir du format matrice d'adjacence */    
void affiche_poids_dot(char *nom_fich,GRAPHE_POIDS g)
{
  FILE *fich;

  fich=fopen(nom_fich,"w");
  if (fich==0)
    {
      printf("erreur opening %s\n",nom_fich);
      exit(EXIT_FAILURE);
    }
  print_poids_dot(fich,g);
  fclose(fich);
  fprintf(stdout,"Graphe written to %s\n",nom_fich);
}

/* affichage à l'écran avec dotty d'un graphe au format dot 
   a partir du format matrice d'adjacence */    
void dotty_poids_dot(GRAPHE_POIDS g)
{
  char *nom="test_graphe.dot";
  char commande[20];
  
  affiche_poids_dot(nom,g);
  sprintf(commande,"dotty %s",nom);
  system(commande);
}


