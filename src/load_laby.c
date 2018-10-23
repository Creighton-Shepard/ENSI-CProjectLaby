#include "../include/head.h"

//main CHOIX 2
char * selectionnerLabyrinthe(char *filename){
    
    clearConsole();
    char **liste;
    int nb_fichier;
    int choix;

    liste=recupererListeFichierRepertoire("data/laby_save/", &nb_fichier);
    if (liste!=NULL){
        do{
            afficherListeFichier(nb_fichier, liste);
            recupererSaisieInteger("\nQuel labyrinthe voulez-vous charger ?\n", &choix);
            clearConsole();
            if (choix<0 || choix>nb_fichier-1){
                printf("Choix incorrect !\n");
            }
        } while (choix<0 || choix > nb_fichier-1);
        strcpy(filename, liste[choix]);
        libererMemoireListeChaine(nb_fichier, liste);
        clearConsole();
        printf("Le labyrinthe \"%s\" a été chargé !\n",filename);
        return filename;
    }
    else{
        clearConsole();
        printf("Pas de fichiers disponible ! Veuillez créer de nouveaux labyrinthe !\n");
        return "Aucun";
    } 
}