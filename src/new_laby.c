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
    int indice_aleatoire;
    int caseElij[4][2]; //tableau de booleen : [0]=Gauche [1]=Haut [2]=Droite [3]=Bas

    initialiserRandom();
    initialiserCaseAdjacente(caseElij);


    do{
        caseAleatoire(t_h, t_v, &case_alea_horiz, &case_alea_verti);
    } while(laby[case_alea_horiz][case_alea_verti].type=='#');
    printf("Random : %d, %d\n",case_alea_horiz,case_alea_verti);
    determinerCaseAdjacenteEligible(&t_h, &t_v, laby, &case_alea_horiz, &case_alea_verti, caseElij);
    do{
        if(caseElij[0][0]==-1 && caseElij[1][0]==-1 && caseElij[2][0]==-1 && caseElij[3][0]==-1){
            printf("No case found\n");
            break;
        }
        indice_aleatoire=entierAleatoire(0,3);
    } while (caseElij[indice_aleatoire][1]==-1);
    printf("%d",indice_aleatoire);
    
}

void initialiserCaseAdjacente(int caseElij[4][2]){
    int i;
    for(int i=0;i<4;i++){
        caseElij[i][0]=-1;
        caseElij[i][1]=-1;
    }
}

void determinerCaseAdjacenteEligible(int *t_h, int *t_v,Case **laby,int *case_alea_horiz, int *case_alea_verti, int caseElij[4][2]){
    if ((*case_alea_horiz)!=1)
    {
        if(laby[*case_alea_horiz-2][*case_alea_verti].type='n'){
            if(laby[*case_alea_horiz][*case_alea_verti].value!=laby[*case_alea_horiz-2][*case_alea_verti].value){
                caseElij[0][0]=*case_alea_horiz-2;
                caseElij[0][1]=*case_alea_verti;
                printf("Une case à gauche !\n");
            }
        }
    }
    if ((*case_alea_verti)!=1)
    {
        if(laby[*case_alea_horiz][*case_alea_verti-2].type='n'){
            if(laby[*case_alea_horiz][*case_alea_verti].value!=laby[*case_alea_horiz][*case_alea_verti-2].value){
                caseElij[1][0]=*case_alea_horiz;
                caseElij[1][1]=*case_alea_verti-2;
                printf("Une case en haut !\n");
            }
        }
    }
    if ((*case_alea_horiz)!=((*t_h)-2))
    {
        if(laby[*case_alea_horiz+2][*case_alea_verti].type='n'){
            if(laby[*case_alea_horiz][*case_alea_verti].value!=laby[*case_alea_horiz+2][*case_alea_verti].value){
                caseElij[2][0]=*case_alea_horiz+2;
                caseElij[2][1]=*case_alea_verti;
                printf("Une case à droite !\n");
            }
        }
    }
    if ((*case_alea_verti)!=((*t_v)-2))
    {
        if(laby[*case_alea_horiz][*case_alea_verti+2].type='n'){
            if(laby[*case_alea_horiz][*case_alea_verti].value!=laby[*case_alea_horiz][*case_alea_verti+2].value){
                caseElij[3][0]=*case_alea_horiz;
                caseElij[3][1]=*case_alea_verti+2;
                printf("Une case en bas !\n");
            }
        }
    }  
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
