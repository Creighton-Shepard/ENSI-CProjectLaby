#include "head.h"

void recupererSaisieInteger(char * phraseDem, int * var){
    if (phraseDem!=NULL){
        printf("%s",phraseDem);
    }
    else{
        printf("Erreur : Pas de phrase dans la fonction de récupération d'Integer");
    }
    scanf("%d",var);
}