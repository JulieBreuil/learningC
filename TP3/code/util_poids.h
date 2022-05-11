GRAPHE_POIDS init_poids_mat(int nb_sommets);
GRAPHE_POIDS read_poids_mat(char *nom_fich);
void affiche_poids_mat(FILE *fich,GRAPHE_POIDS g);
void print_poids_dot(FILE *fich,GRAPHE_POIDS g);
void affiche_poids_dot(char *nom_fich,GRAPHE_POIDS g);
void dotty_poids_dot(GRAPHE_POIDS g);



