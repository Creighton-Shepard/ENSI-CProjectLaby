#include "../include/head.h"

void afficherMenu(){
    printf("\nMENU :\n");
    printf("\t(1) Créer un nouveau Labyrinthe\n");
    printf("\t(2) Charger un nouveau Labyrinthe\n");
    printf("\t(3) Jouer\n");
    printf("\t(4) Quitter\n");
}

void afficherLabyrinthe(int t_h, int t_v, Case **laby){
    int i,j;

    for(i=0;i<t_v;i++){
        for(j=0;j<t_h;j++){
            if (laby[j][i].type=='n')
            {
                printf("%d",laby[j][i].value);
            }
            else if (laby[j][i].type=='v'){
                printf(" ");
            }
            else
            {
                printf("%c",laby[j][i].type);
            }
        }
        printf("\n");
    }
}

void clearConsole(){
    system("clear");
}

void afficherListeFichier(int len_liste, char **liste_fichier){
    int i;

    printf("Liste des Labyrinthe disponible :\n\n");
    for(i=0;i<len_liste;i++){
        printf("(%d) = %s\n",i,liste_fichier[i]);
    }
}

void afficherTableauScore(Gagnant *tab_score){
    int i=0;

    printf("Liste des Gagnants :\n\n");
    for(i=0;i<NB_GAGNANT;i++){
        if (tab_score[i].place!=-1){
            printf("%d - %s - %d\n", tab_score[i].place, tab_score[i].nom_gagnant, tab_score[i].score);
        }
    }
}
