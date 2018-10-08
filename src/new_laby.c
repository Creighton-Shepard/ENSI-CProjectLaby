#include "../include/head.h"

//main CHOIX 1
void nouveauLabyrinthe(){
    int taille_horiz;
    int taille_verti;

    clearConsole();
    printf("Nouveau Labyrynthe !\n");
    recupererSaisieInteger("Indiquer la taille horizontale du nouveau labyrinthe :\n",&taille_horiz);
    recupererSaisieInteger("Indiquer la taille verticale du nouveau labyrinthe :\n",&taille_verti);
    clearConsole();

    Case **laby;
    laby=allouerMemoireLabyrinthe(taille_horiz, taille_verti, laby);
    initialiserLabyrinthe(taille_horiz, taille_verti, laby);
    afficherLabyrinthe(taille_horiz,taille_verti, laby);
    construireLabyrinthe(taille_horiz,taille_verti, laby);

    recupererSaisieInteger("Truc",&taille_horiz);
    libererMemoireLabyrinthe(taille_horiz, laby);
}

void initialiserLabyrinthe(int t_h, int t_v,Case **laby){
    int i,j;
    int cpt=1;

    for(i=0;i<t_h;i++){
        for(j=0;j<t_v;j++){
            if ((i%2==0) || (j%2==0))
            {
                laby[i][j].type='#';
            }
            else
            {
                laby[i][j].type='n';
                laby[i][j].value=cpt;
                cpt++;
            }  
        }
    }
}

void construireLabyrinthe(int t_h, int t_v,Case **laby){
    int case_alea_horiz=0;
    int case_alea_verti=0;

    caseAleatoire(t_h, t_v, &case_alea_horiz, &case_alea_verti);
    printf("%d, %d",case_alea_horiz,case_alea_verti);
}

void caseAleatoire(int t_h, int t_v,int * case_alea_horiz, int * case_alea_verti ){
    srand(time(NULL));

    *case_alea_horiz=((int)rand()/RAND_MAX)* t_h + 1;
    *case_alea_verti=((int)rand()/RAND_MAX)* t_v + 1;
}

Case** allouerMemoireLabyrinthe(int t_h, int t_v, Case **laby){
    int i;
    
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
