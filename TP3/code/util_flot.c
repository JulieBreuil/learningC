#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphe_flot_type.h"
#include "util_flot.h"


/* Initialisation d'un graphe valué (type GRAPHE_FLOT)  de nb_sommets (sans arcs) */
GRAPHE_FLOT init_flot_mat(int nb_sommets)
{
  GRAPHE_FLOT g;

  g.nb_sommets=nb_sommets;
  g.adj=(int **)malloc(nb_sommets*sizeof(int*));
  g.poids=(int **)malloc(nb_sommets*sizeof(int*));
  g.flot=(int **)malloc(nb_sommets*sizeof(int*));
  if ((g.adj==(int **)NULL)||(g.poids==(int **)NULL)||(g.flot==(int **)NULL))
    {
      printf("Error: no more memory\n");
      exit(EXIT_FAILURE);
    }
  for (int i=0;i<nb_sommets;i++)
    {
      g.adj[i]=(int *)malloc(nb_sommets*sizeof(int));
      g.poids[i]=(int *)malloc(nb_sommets*sizeof(int));
      g.flot[i]=(int *)malloc(nb_sommets*sizeof(int));
      if ((g.adj[i]==(int *)NULL)||(g.poids[i]==(int *)NULL)||
	  (g.poids[i]==(int *)NULL))
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
	g.flot[i][j]=0;
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

/* lecture de trois matrices (adjacence, poids et flot) dans un fichier, creation du graphe correspondant */
GRAPHE_FLOT read_flot_mat(char *nom_fich)
{
  int res;
  int nbRows,nbColumns,nbRows2,nbColumns2,nbRows3,nbColumns3,val;
  GRAPHE_FLOT g;
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
  g=init_flot_mat(nbRows);
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
       if ((val != 0)&&(g.adj[i][j]==0))
	 {
	   fprintf(stderr,"Warning, l'arc %d -> %d  a un poids mais pas d'arc\n",
		   i+1,j+1);
	 }
       g.poids[i][j]=val;
     }
  fscanf(fich, "%d",&nbRows3);
  fscanf(fich, "%d",&nbColumns3);
  if ((nbRows3!=nbRows) || (nbColumns3!=nbRows))
    {
      printf("erreur matrice de flot non conforme\n");
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
       if ((val != 0) && (g.adj[i][j]==0))
	 {
	   fprintf(stderr,"Warning, l'arc %d -> %d  a un flot mais pas d'arc\n",
		   i+1,j+1);
	 }
       g.flot[i][j]=val;
     }
 return g;
}

/* affichage des trois matrices (adjacence, poids et flot ) d'un graphe valué
  dans un fichier */
void affiche_flot_mat(FILE *fich,GRAPHE_FLOT g)
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
  fprintf(fich,"%4d %4d",nb_sommets,nb_sommets);
  fprintf(fich,"     ");
  fprintf(fich,"     ");
  for  (int i=0;i<nb_sommets;i++)
    {
      fprintf(fich,"\n");
      for (int j=0;j<nb_sommets;j++)
	{
	  fprintf(fich," %4d ",g.flot[i][j]);
	}
    }	      
  fprintf(fich,"\n");
}  



/* affichage d'un graphe valué au format dot 
   a partir du type GRAPHE_FLOT */    
void print_flot_dot(FILE *fich,GRAPHE_FLOT g)
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
	      fprintf(fich,"[ label=\"%d (%d)\" ];\n",g.poids[i][j],g.flot[i][j]);
	    }
	}
    }
  fprintf(fich,"}\n");
}
  

/* affichage (dans un fichier) d'un graphe au format dot 
   a partir du format matrice d'adjacence */    
void affiche_flot_dot(char *nom_fich,GRAPHE_FLOT g)
{
  FILE *fich;

  fich=fopen(nom_fich,"w");
  if (fich==0)
    {
      printf("erreur opening %s\n",nom_fich);
      exit(EXIT_FAILURE);
    }
  print_flot_dot(fich,g);
  fclose(fich);
  fprintf(stdout,"Graphe written to %s\n",nom_fich);
}

/* affichage à l'écran avec dotty d'un graphe au format dot 
   a partir du format matrice d'adjacence */    
void dotty_flot_dot(GRAPHE_FLOT g)
{
  char *nom="test_graphe.dot";
  char commande[20];
  
  affiche_flot_dot(nom,g);
  sprintf(commande,"dotty %s",nom);
  system(commande);
}


