#ifndef _MENU
#define _MENU

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <dirent.h>
#include <sys/types.h>

#define RAND_MAX 2147483647
#define NB_CHAR_FILE_NAME 30

typedef struct{
    char type; // #=Mur o=Personnage n=Valeur(nombre pour la construction) v=vide(après construction)...
    int value;
} Case;

//affichage.c
void afficherMenu();
void clearConsole();
void afficherLabyrinthe(int t_h, int t_v, Case **laby);
void afficherListeFichier(int len_liste, char **liste_fichier);

//new_laby.c
char * nouveauLabyrinthe(char *filename);
void initialiserLabyrinthe(int t_h, int t_v,Case **laby);
void construireLabyrinthe(int t_h, int t_v,Case **laby);
void determinerCaseAdjacenteEligible(int *t_h, int *t_v,Case **laby,int *case_alea_horiz, int *case_alea_verti, int caseElij[4][2]);
void initialiserCaseAdjacente(int caseElij[4][2]);
void casserMurChoisi(Case ** laby, int caseElij[4][2], int indice);
void corrigerIndice(int t_h, int t_v, Case ** laby, int new_valeur, int ancien_valeur);
int verifierLabyrinthe(int t_h,int t_v,Case ** laby);
void steriliserLabyrintheApresConstruction(int t_h, int t_v, Case ** laby);


//saisie.c
void recupererSaisieInteger(char * phraseDem, int * var);
void demanderEntierSigneImpair(char * phraseDem, int * var);
void recupererSaisieString(char * phraseDem, char *var);
void viderBuffer();

//aleatoire.c
void caseAleatoire(int t_h, int t_v,int * case_alea_horiz, int * case_alea_verti );
int entierAleatoire(int min, int max);
void initialiserRandom();
int entierAleatoireParmiListe(int caseElij[4][2]);

//file.c
void enregistrerLabyrinthe(int t_h, int t_v, Case **laby, char *filename);
char ** recupererListeFichierRepertoire(char * repertoire, int *len_liste);
int trouverNombreFichierDansRepertoire(char * repertoire);
Case ** chargerLabyrinthe(char * filename, int *t_h, int *t_v);
void recupererDimensionLabyrinthe(FILE *fd, int *t_h, int *t_v);
void recupererDonneesLabyrinthe(FILE *fd, int t_h, int t_v, Case **laby);


//load_laby.c
char * selectionnerLabyrinthe(char *filename);

//memoire.c
char ** allouerMemoireListeFichier(int len_liste);
void libererMemoireListeFichier(int len_liste, char ** liste);
Case** allouerMemoireLabyrinthe(int t_h, int t_v);
void libererMemoireLabyrinthe(int t_h, Case **laby);

//play.c
void jouer(char *filename);
void lancerBoucleDeJeu(int t_h, int t_v, Case **laby);
void rechercherEmplacementJoueur(int *player_h, int *player_v, int t_h, int t_v, Case **laby);
void rechercherEmplacementSortie(int *exit_h, int *exit_v, int t_h, int t_v, Case **laby);
Case ** deplacerElementDansLaby(int *ex_h, int *ex_v, int new_h, int new_v, int t_h, int t_v, Case **laby);
int testerFinDuJeu(int exit_h, int exit_v, Case **laby);
/* Code fournie par la source */
void set_mode(int want_key);
int get_key();
/* FIN - Code fournie par la source */

#endif