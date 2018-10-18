#include "../include/head.h"

//main CHOIX 2
void chargerLabyrinthe(char *filename){
    
    clearConsole();
    char **liste;
    int nb_fichier;

    printf("Liste des Labyrinthe disponible :\n");
    recupererListeFichierRepertoire("data/", liste, &nb_fichier);
    libererMemoireListeFichier(nb_fichier, liste);
}