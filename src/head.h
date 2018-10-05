#ifndef _MENU
#define _MENU

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char type; // #=Mur o=Personnage ...
} Case;

//affichage.c
void afficherMenu();
void clearConsole();
void afficherLabyrinthe(int t_h, int t_v, Case **laby);

//new_laby.c
void nouveauLabyrinthe();
void initialiserLabyrinthe(int t_h, int t_v,Case **laby);
Case** allouerMemoireLaby(int t_h, int t_v, Case **laby);
void libererMemoireLaby(int t_h, Case **laby);

//saisie.c
void recupererSaisieInteger(char * phraseDem, int * var);

#endif