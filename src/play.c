#include "../include/head.h"

/**
 * Source :
 *  - Gestion du clavier: "https://rosettacode.org/wiki/Keyboard_input/Keypress_check"
 */
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

//Main choix 3 du menu
void jouer(char *filename){
    Case ** laby;
    int tail_horiz;
    int tail_verti;

    if(strcmp(filename, "Aucun")==0){
        printf("Pas de labyrinthe chargé !\n");
    }
    else{
        laby=chargerLabyrinthe(filename, &tail_horiz, &tail_verti);
        lancerBoucleDeJeu(tail_horiz, tail_verti, laby);
    }
}

void lancerBoucleDeJeu(int t_h, int t_v, Case **laby){
    clearConsole();
    afficherLabyrinthe(t_h, t_v, laby);
}