#include "../include/head.h"

void recupererSaisieInteger(char * phraseDem, int * var){
    if (phraseDem!=NULL){
        printf("%s",phraseDem);
    }
    else{
        printf("Erreur : Pas de phrase dans la fonction de récupération d'Integer");
    }
    scanf("%d",var);
    viderBuffer();
}

void demanderEntierSigneImpair(char * phraseDem, int * var){
    do{
        recupererSaisieInteger(phraseDem,var);
        if (*var%2==0){
            clearConsole();
            printf("Cette donnée doit être impaire !\n");
        }
        else if(*var<5){
            clearConsole();
            if (*var<=0){                        
                printf("Cette donnée doit être strictement positive !\n");
            }
            else
            {
                printf("Cette donnée doit être supérieure ou égale à 5 !\n");
            }
        }
    } while (*var%2==0 || *var<5);
}

void recupererSaisieString(char * phraseDem, char ** var){
    if (phraseDem!=NULL){
        printf("%s",phraseDem);
    }
    else{
        printf("Erreur : Pas de phrase dans la fonction de récupération de String");
    }
    scanf("%s",*var);
    viderBuffer();
}

void viderBuffer(){
    int c=0;
    while (c!= '\n' && c!=EOF){
        c=getchar();
    }
}