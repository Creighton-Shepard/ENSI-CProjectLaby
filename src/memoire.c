#include "../include/head.h"

// typechaine: 'f'=liste de fichiers / 'g'=liste de gagnants
char ** allouerMemoireListeChaine(int len_liste){
    int i;
    char ** liste;

    liste=(char **)malloc(len_liste*sizeof(char *));
    if (liste==NULL){
        printf("Erreur dans la création de la dimension principale du tableau\n");
    }    
    for(i=0;i<len_liste;i++){
        liste[i]=(char *)malloc(NB_CHAR_STRING*sizeof(char));
        if (liste[i]==NULL){
            int j;
            printf("Erreur dans la création du sous tableau %d \n",i);
            //si une erreur est survenue il faut liberer tout ce qui a déjà été alloué
            for(j=i-1;j>=0;j++){
                free(liste[j]);
            }
            free(liste);
        }
    }
    return liste;
}

void libererMemoireListeChaine(int len_liste, char **liste){
    int i;
    for(i=0; i<len_liste; i++){
        free(liste[i]);
    }
    free(liste);
}

Case** allouerMemoireLabyrinthe(int t_h, int t_v){
    int i;
    Case **laby;

    laby=(Case **)malloc(t_h * sizeof(Case *));
    if (laby==NULL){
        printf("Erreur dans la création de la dimension principale du tableau\n");
    }    
    for(i=0;i<t_h;i++){
        laby[i]=(Case *)malloc(t_v*sizeof(Case));
        if (laby[i]==NULL){
            int j;
            printf("Erreur dans la création du sous tableau %d \n",i);
            //si une erreur est survenue il faut liberer tout ce qui a déjà été alloué
            for(j=i-1;j>=0;j++){
                free(laby[j]);
            }
            free(laby);
        }
    }
    return laby;
}

void libererMemoireLabyrinthe(int t_h, Case **laby){
    int i;

    for(i=0; i<t_h; i++){
        free(laby[i]);
    }
    free(laby);
}

Gagnant * allouerMemoireTableauScore(int len_liste){
    Gagnant *liste=NULL;

    liste=(Gagnant *)malloc(len_liste*sizeof(Gagnant));
    if (liste==NULL){
        printf("Erreur dans la création de la dimension principale du tableau\n");
    }
    return liste;
}
