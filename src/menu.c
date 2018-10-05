#include "head.h"

int main(int argc, char * argv[])
{
    int end_of_game; //0 ou 1
    int choix;

    clearConsole();
    if(argc>1){
        printf("WARNING ! Ce programme n'a pas besoin d'argument au lancement : %d arguments trouvé(s). \n",argc);
    }
    end_of_game=0;
    while(!end_of_game)
    {
        do{
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
                nouveauLabyrinthe();
                break;
            case 2:
                printf("Charger Labyrynthe !\n");
                break;
            case 3:
                printf("Jouer !\n");
                break;
            case 4:
                printf("Fin du jeu !\nBonne journée !\n");
                end_of_game=1;
                break;
        }
    }
    return 0;
}