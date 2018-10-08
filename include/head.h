#ifndef _MENU
#define _MENU

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct{
    char type; // #=Mur o=Personnage ...
    int value;
} Case;

//affichage.c
void afficherMenu();
void clearConsole();
void afficherLabyrinthe(int t_h, int t_v, Case **laby);

//new_laby.c
void nouveauLabyrinthe();
void initialiserLabyrinthe(int t_h, int t_v,Case **laby);
Case** allouerMemoireLabyrinthe(int t_h, int t_v, Case **laby);
void libererMemoireLabyrinthe(int t_h, Case **laby);
void construireLabyrinthe(int t_h, int t_v,Case **laby);
void caseAleatoire(int t_h, int t_v,int * case_alea_horiz, int * case_alea_verti );

//saisie.c
void recupererSaisieInteger(char * phraseDem, int * var);

#endif