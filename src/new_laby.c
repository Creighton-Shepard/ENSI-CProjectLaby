#include "../include/head.h"


//main CHOIX 1
char * nouveauLabyrinthe(char *filename){
    int taille_horiz;
    int taille_verti;

    clearConsole();
    printf("Nouveau Labyrinthe !\n");
    demanderEntierSigneImpair("Indiquer la taille horizontale du nouveau labyrinthe :\n",&taille_horiz);
    demanderEntierSigneImpair("Indiquer la taille verticale du nouveau labyrinthe :\n",&taille_verti);
    clearConsole();

    Case **laby;
    laby=allouerMemoireLabyrinthe(taille_horiz, taille_verti);
    initialiserLabyrinthe(taille_horiz, taille_verti, laby);
    construireLabyrinthe(taille_horiz,taille_verti, laby);

    recupererSaisieString("\nQuel est le nom du labyrinthe ?\n",filename);
    enregistrerLabyrinthe(taille_horiz, taille_verti, laby, filename);
    libererMemoireLabyrinthe(taille_horiz, laby);
    clearConsole();
    printf("Création du labyrinthe \"%s\" réussie !\n",filename);
    return filename;
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

    do{
        initialiserCaseAdjacente(caseElij);
        do{
            caseAleatoire(t_h, t_v, &case_alea_horiz, &case_alea_verti);
        } while(laby[case_alea_horiz][case_alea_verti].type=='#');
        determinerCaseAdjacenteEligible(&t_h, &t_v, laby, &case_alea_horiz, &case_alea_verti, caseElij);
        if (!(caseElij[0][0]==-1 && caseElij[1][0]==-1 && caseElij[2][0]==-1 && caseElij[3][0]==-1)){
            indice_aleatoire=entierAleatoireParmiListe(caseElij);
            casserMurChoisi(laby,caseElij, indice_aleatoire);
            corrigerIndice(t_h,t_v,laby,laby[case_alea_horiz][case_alea_verti].value,laby[caseElij[indice_aleatoire][0]][caseElij[indice_aleatoire][1]].value);
        }
    } while(verifierLabyrinthe(t_h, t_v, laby)==0);

    steriliserLabyrintheApresConstruction(t_h, t_v, laby);
    laby[0][1].type='o';
    laby[t_h-1][t_v-2].type='v';
    placerObjet('X', t_h, t_v, laby);
    placerObjet('T', t_h, t_v, laby);
    afficherLabyrinthe(t_h, t_v, laby);
}

void placerObjet(char objet, int t_h, int t_v, Case **laby){
    int nb_tresor;
    int case_alea_h, case_alea_v;
    int percent;

    switch (objet){
        case 'X':
            percent=PIEGE_PERCENT;
            break;
        case 'T':
            percent=TRESOR_PERCENT;
            break;
    }
    nb_tresor=(int)round(t_h * t_v * percent / 100);

    while (nb_tresor>=0){
        do{
            caseAleatoire(t_h, t_v, &case_alea_h, &case_alea_v);
        } while (laby[case_alea_h][case_alea_v].type!='v');
        laby[case_alea_h][case_alea_v].type=objet;
        nb_tresor--;
    }
}


//Enlever les valeurs des cases à la fin de la construction
void steriliserLabyrintheApresConstruction(int t_h, int t_v, Case ** laby){
    int i, j;
    for (i=0; i<t_h; i++){
        for(j=0; j<t_v; j++){
            if (laby[i][j].type=='n'){
                laby[i][j].type='v';
            }
        }
    }
}

int verifierLabyrinthe(int t_h,int t_v,Case ** laby){
    int ind=-1;
    int i, j;

    for(i=1;i<t_h-1;i++){
        for(j=1;j<t_v-1;j++){
            if (laby[i][j].type=='n'){
                if(ind==-1){
                    ind=laby[i][j].value;
                }
                else
                {
                    if(ind!=laby[i][j].value){
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

void corrigerIndice(int t_h, int t_v, Case ** laby, int new_valeur, int ancien_valeur){
    int i, j;
    
    for (i=1; i<t_h-1; i++){
        for(j=1; j<t_v-1; j++){
            if(laby[i][j].type=='n'){
                if(laby[i][j].value==ancien_valeur){
                    laby[i][j].value=new_valeur;
                }
            }
        }
    }
}

void casserMurChoisi(Case ** laby, int caseElij[4][2], int indice){
    int coordMur_h;
    int coordMur_v;

    coordMur_h=caseElij[indice][0];
    coordMur_v=caseElij[indice][1];
    switch(indice){
        case 0:
            coordMur_h++;
            break;
        case 1:
            coordMur_v++;
            break;
        case 2:
            coordMur_h--;
            break;
        case 3:
            coordMur_v--;
            break;
        default:
            printf("Erreur: Indice de Mur incorrecte !\n");
    }
    laby[coordMur_h][coordMur_v].type='n';
    laby[coordMur_h][coordMur_v].value=laby[caseElij[indice][0]][caseElij[indice][1]].value;
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
        if(laby[*case_alea_horiz-2][*case_alea_verti].type=='n'){
            if(laby[*case_alea_horiz][*case_alea_verti].value!=laby[*case_alea_horiz-2][*case_alea_verti].value){
                caseElij[0][0]=*case_alea_horiz-2;
                caseElij[0][1]=*case_alea_verti;
            }
        }
    }
    if ((*case_alea_verti)!=1)
    {
        if(laby[*case_alea_horiz][*case_alea_verti-2].type=='n'){
            if(laby[*case_alea_horiz][*case_alea_verti].value!=laby[*case_alea_horiz][*case_alea_verti-2].value){
                caseElij[1][0]=*case_alea_horiz;
                caseElij[1][1]=*case_alea_verti-2;
            }
        }
    }
    if ((*case_alea_horiz)!=((*t_h)-2))
    {
        if(laby[*case_alea_horiz+2][*case_alea_verti].type=='n'){
            if(laby[*case_alea_horiz][*case_alea_verti].value!=laby[*case_alea_horiz+2][*case_alea_verti].value){
                caseElij[2][0]=*case_alea_horiz+2;
                caseElij[2][1]=*case_alea_verti;
            }
        }
    }
    if ((*case_alea_verti)!=((*t_v)-2))
    {
        if(laby[*case_alea_horiz][*case_alea_verti+2].type=='n'){
            if(laby[*case_alea_horiz][*case_alea_verti].value!=laby[*case_alea_horiz][*case_alea_verti+2].value){
                caseElij[3][0]=*case_alea_horiz;
                caseElij[3][1]=*case_alea_verti+2;
            }
        }
    }  
}
