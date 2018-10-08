#include "../include/head.h"

void afficherMenu(){
    printf("Bienvenue sur le jeu du Labyrinthe !\n\n");
    printf("MENU :\n");
    printf("\t(1) Créer un nouveau Labyrinthe\n");
    printf("\t(2) Charger un nouveau Labyrinthe\n");
    printf("\t(3) Jouer\n");
    printf("\t(4) Quitter\n");
}

void afficherLabyrinthe(int t_h, int t_v, Case **laby){
    int i,j;

    for(i=0;i<t_h;i++){
        for(j=0;j<t_v;j++){
            if (laby[i][j].type=='n')
            {
                printf("%d",laby[i][j].value);
            }
            else
            {
                printf("%c",laby[i][j].type);
            }
        }
        printf("\n");
    }
}

void clearConsole(){
    system("clear");
}