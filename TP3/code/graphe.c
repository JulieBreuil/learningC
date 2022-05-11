#include "graphe.h"

void fermeture_transistive2(GRAPHE g);

GRAPHE fermeture_transistive(GRAPHE g){
    int modif = 1;
    GRAPHE g2=g;
    while (modif==1){
        modif = 0;
        for (int i = 0 ; i < g.nb_sommets ; i++)
        {
            for (int j = 0; j<g.nb_sommets; j++)
            {
                if (g2.adj[i][j]==1)
                {
                    for (int k = 0; k<g.nb_sommets; k++)
                    {
                        if (g2.adj[j][k]==1){
                            if (g2.adj[i][k]!=1){
                                g2.adj[i][k]=1;
                                modif = 1;
                            }
                        }
                    }
                }
            }
        } 
    } 
    return g2;
}

int marque (GRAPHE_POIDS g){
    int tout_marque = 1;
    for (int i =0; i<g.nb_sommets; i++){
        if (g.marque[i]==0){
            tout_marque = 0;
        }
    }
    return tout_marque; 
}

int min (int poids[]){
    int min = poids[0];
    for (int i=0;i<sizeof(poids);i++){
        if (poids[i]<min){
            min=poids[i];
        }
    }
    return min;
}

int valMin (int poids[]){
    int valMin=0;
    for (int i=0;i<sizeof(poids);i++){
        if (poids[i]<min){
            valMin=0;
        }
    }
    return min;
}


int *dijkstra(GRAPHE_POIDS g,int source){
    /*function Dijkstra(Graph, source):

    for each vertex v in Graph.Vertices:            
        dist[v] ← INFINITY                 
        prev[v] ← UNDEFINED                
        add v to Q                     
    dist[source] ← 0                       
    
    while Q is not empty:
        u ← vertex in Q with min dist[u]   
        remove u from Q
                                        
        for each neighbor v of u still in Q:
            alt ← dist[u] + Graph.Edges(u, v)
            if alt < dist[v]:              
                dist[v] ← alt
                prev[v        int liste_marque [g.nb_sommets];v[]*/

    for (int i = 0; i<g.nb_sommets; i++){
        int prev [g.nb_sommets][g.nb_sommets];
        /*poids = correspond aux différents sommets*/
        if (i!=source)
        {
            for (int i = 0; i<g.nb_sommets; i++){
                
            }
            g.poids[i][source]=1000;
        }

        while (marque(g)==0){
            int u = valMin(cout[i]);
            g.marque[u]=1;

        }
        /*tant que tous les neouds ne sont pas marqués*/
            /*parmi tous les noeuds qui ne sont pas marqués, chercher celui qui a le eplus petit poids u*/
            /*marquer le neoud u*/
            /*le supprimer du tableau cout*/
            /*Pour tous les voisins de u*/
                /*
                alt ← dist[u] + Graph.Edges(u, v)
                    if alt < dist[v]:              
                        dist[v] ← alt
                        prev[v] ← u

                */

    }
}