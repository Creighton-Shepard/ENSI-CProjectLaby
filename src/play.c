#include "../include/head.h"

/**
 * Source :
 *  - Gestion du clavier: "https://rosettacode.org/wiki/Keyboard_input/Keypress_check"
 */
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

//Main choix 3 du menu
void jouer(char *filename){
    Case ** laby;
    int tail_horiz;
    int tail_verti;

    if(strcmp(filename, "Aucun")==0){
        printf("Pas de labyrinthe chargé !\n");
    }
    else{
        laby=chargerLabyrinthe(filename, &tail_horiz, &tail_verti);
        lancerBoucleDeJeu(tail_horiz, tail_verti, laby);
    }
    clearConsole();
}

void lancerBoucleDeJeu(int t_h, int t_v, Case **laby){
    int player_h, player_v;
    int score=0;
    int exit_h, exit_v;
    int key_code;
    int end_game=0;

    rechercherEmplacementJoueur(&player_h, &player_v, t_h, t_v, laby);
    rechercherEmplacementSortie(&exit_h, &exit_v, t_h, t_v, laby);
    /* Debut boucle de jeu */
    while(!testerFinDuJeu(exit_h, exit_v, laby)){
        clearConsole();
        afficherLabyrinthe(t_h, t_v, laby);
        printf("\nScore : %d\nPOS JOUEUR : %d, %d\n",score, player_h, player_v);
        set_mode(1); /* Active la caputure du clavier */
        /* En attente d'un evenement "Touche pressé" */
        while (!(key_code = get_key())){
            usleep(10000);
        }
		switch (key_code){
            case 122:
                laby=deplacerElementDansLaby(&player_h, &player_v, player_h, player_v-1, t_h, t_v, laby);
                break;
            case 113:
                laby=deplacerElementDansLaby(&player_h, &player_v, player_h-1, player_v, t_h, t_v, laby);
                break;
            case 100:
                laby=deplacerElementDansLaby(&player_h, &player_v, player_h+1, player_v, t_h, t_v, laby);
                break;
            case 115:
                laby=deplacerElementDansLaby(&player_h, &player_v, player_h, player_v+1, t_h, t_v, laby);
                break;
        }
    }
    clearConsole();
    afficherLabyrinthe(t_h, t_v, laby);
    recupererSaisieInteger("Fin de jeu", NULL);

}

void rechercherEmplacementJoueur(int *player_h, int *player_v, int t_h, int t_v, Case **laby){
    int i,j;
    for (i=0; i<t_h; i++){
        for(j=0; j<t_v; j++){
            if (laby[i][j].type=='o'){
                break;
            }
        }
        if (laby[i][j].type=='o'){
            break;
        }
    }
    *player_h=i;
    *player_v=j;
}

void rechercherEmplacementSortie(int *exit_h, int *exit_v, int t_h, int t_v, Case **laby){
    int i,j;
    for (i=0; i<t_h; i++){
        if(i==0 || i==t_h-1){
            for (j=0; j<t_v; j++){
                if(laby[i][j].type=='v'){
                    break;
                }
            }
            if(laby[i][j].type=='v'){
                break;
            }
        }
        else{
            if(laby[i][0].type=='v'){
                j=0;
            }
            if(laby[i][t_v-1].type=='v'){
                j=t_v-1;
            }
        }
    }
    *exit_h=i;
    *exit_v=j;
}


Case ** deplacerElementDansLaby(int *ex_h, int *ex_v, int new_h, int new_v, int t_h, int t_v, Case **laby){
    if ((new_h != *ex_h || new_v != *ex_v) && (new_h>=0 && new_v>=0 && new_h<t_h && new_v<t_v)){
        if (laby[new_h][new_v].type!='#'){
            laby[new_h][new_v].type=laby[*ex_h][*ex_v].type;
            laby[*ex_h][*ex_v].type='v';
            *ex_h=new_h;
            *ex_v=new_v;
        }
    }
    return laby;
}

int testerFinDuJeu(int exit_h, int exit_v, Case **laby){
    if(laby[exit_h][exit_v].type=='o'){
        return 1;
    }
    else{
        return 0;
    }
}

/* Code fournie par la source */
void set_mode(int want_key)
{
	static struct termios old, new;
	if (!want_key) {
		tcsetattr(STDIN_FILENO, TCSANOW, &old);
		return;
	}
 
	tcgetattr(STDIN_FILENO, &old);
	new = old;
	new.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
}
 
/* Code fournie par la source */
int get_key()
{
	int c = 0;
	struct timeval tv;
	fd_set fs;
	tv.tv_usec = tv.tv_sec = 0;
 
	FD_ZERO(&fs);
	FD_SET(STDIN_FILENO, &fs);
	select(STDIN_FILENO + 1, &fs, 0, 0, &tv);
 
	if (FD_ISSET(STDIN_FILENO, &fs)) {
		c = getchar();
		set_mode(0);
	}
	return c;
}