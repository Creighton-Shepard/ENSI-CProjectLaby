#include "../include/head.h"

int main(int argc, char * argv[])
{
    int end_of_game; //0 ou 1
    int choix;
    char *filename;

    filename=(char*)malloc(NB_CHAR_FILE_NAME*sizeof(char));
    strcpy(filename,"Aucun");
    clearConsole();
    if(argc>1){
        printf("WARNING ! Ce programme n'a pas besoin d'argument au lancement : %d arguments trouvé(s). \n",argc);
    }
    printf("Bienvenue sur le jeu du Labyrinthe !\n\n");
    end_of_game=0;
    while(!end_of_game)
    {
        do{
            printf("\nLabyrinthe actuel : %s\n", filename);
            afficherMenu();
            recupererSaisieInteger("Que voulez-vous faire ? (Entrez le chiffre associé)\n", &choix);
            clearConsole();
            if (choix<1 || choix>4){
                printf("Choix incorrect !\n");
            }
        } while(choix<1 || choix>4);
        clearConsole();
        switch(choix)
        {
            case 1:
                filename=nouveauLabyrinthe(filename);
                break;
            case 2:
                filename=selectionnerLabyrinthe(filename);
                break;
            case 3:
                jouer(filename);
                break;
            case 4:
                printf("Fin du jeu !\nBonne journée !\n");
                end_of_game=1;
                free(filename);
                break;
        }
    }
    return 0;
}