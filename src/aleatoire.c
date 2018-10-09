#include "../include/head.h"

void initialiserRandom(){
    srand(time(NULL));
}

void caseAleatoire(int t_h, int t_v,int * case_alea_horiz, int * case_alea_verti ){
    *case_alea_horiz=entierAleatoire(0,t_h-1); 
    *case_alea_verti=entierAleatoire(0,t_v-1); 
}

int entierAleatoire(int min, int max){
    return ((double)rand()/RAND_MAX)*max+min;
}