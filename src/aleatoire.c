#include "../include/head.h"

void caseAleatoire(int t_h, int t_v,int * case_alea_horiz, int * case_alea_verti ){
    *case_alea_horiz=rand() % t_h; //renvoie un int entre 0 et t_h-1
    *case_alea_verti=rand() % t_v; 
}