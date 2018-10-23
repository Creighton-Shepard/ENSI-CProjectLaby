#include "../include/head.h"

void enregistrerLabyrinthe(int t_h, int t_v, Case **laby, char *filename){
    FILE *fd=NULL;
    int i,j;
    char chemin[NB_CHAR_STRING+9];

    sprintf(chemin,"data/laby_save/%s.txt",filename);
    printf("Chemin du fichier : %s\n",chemin);
    fd=fopen(chemin,"w");

    if (fd==NULL){
        perror("Erreur création du fichier de sauvegarde\n");
    }
    else{
        printf("Ecriture en cours\n");
        char deb_file[15];

        sprintf(deb_file, "%d , %d \n",t_h,t_v);
        printf("Deb file : %s \n",deb_file);
        fputs(deb_file,fd);

        for(i=0; i<t_v;i++){
            for(j=0; j<t_h; j++){
                if (laby[j][i].type=='v'){
                    fputc(' ', fd);
                }
                else{
                    fputc(laby[j][i].type, fd);
                }
            }
            fputc('\n', fd);
        }
        initialiserFichierScore(filename);

        if (fclose(fd)==EOF){
            perror("Erreur dans la fermeture du fichier\n");
        }
    } 
}

void initialiserFichierScore(char *filename){
    FILE *fd=NULL;
    char chemin[NB_CHAR_STRING+9];

    sprintf(chemin,"data/laby_score/%s.txt",filename);
    fd=fopen(chemin,"w");
    if (fclose(fd)==EOF){
        perror("Erreur dans la fermeture du fichier\n");
    }
}

char ** recupererListeFichierRepertoire(char * repertoire, int *len_liste){
    char ** liste_fichier=NULL;
    *len_liste=trouverNombreFichierDansRepertoire(repertoire);
    printf(">> %d fichiers trouvés \n", *len_liste);
    if (*len_liste>0){
        DIR *repo= opendir(repertoire);
        if (repo != NULL){
            struct dirent *red_dir;
            int len_filename;
            int cpt=0;
 
            liste_fichier=allouerMemoireListeChaine(*len_liste);
        
            while (red_dir=readdir(repo)){
                len_filename=strlen(red_dir->d_name);
                if (len_filename>4){
                    while (len_filename > 0 && red_dir->d_name[len_filename]!='.'){
                        len_filename--;
                    }
                    if (len_filename!=0){
                        red_dir->d_name[len_filename]='\0';
                    }
                    strcpy(liste_fichier[cpt],red_dir->d_name);
                    //printf("%s\n", red_dir->d_name);
                    cpt++;
                }
            }
        }
        else{
            perror("Erreur dans l'affichage des fichiers d'un dossier\n");
        }
        closedir(repo);
        
    }
    return liste_fichier;
}

int trouverNombreFichierDansRepertoire(char * repertoire){
    DIR *repo= opendir(repertoire);
    int nb_file=0;
    if (repo != NULL){
        
        struct dirent *red_dir;
        while (red_dir=readdir(repo)){
            nb_file++;
        }
        
    }
    closedir(repo);
    return nb_file-2; // pour ne pas compter . et .. qui ne sont pas des fichiers
}

Case ** chargerLabyrinthe(char * filename, int *t_h, int *t_v){
    Case **laby;
    FILE *fd=NULL;
    char chemin[NB_CHAR_STRING+9];

    sprintf(chemin,"./data/laby_save/%s.txt",filename);
    printf("Chemin du fichier : %s\n",chemin);
    fd=fopen(chemin,"r");
    if (fd!=NULL){
        recupererDimensionLabyrinthe(fd, t_h, t_v);
        printf("Dimension : %d, %d\n", *t_h, *t_v);

        laby=allouerMemoireLabyrinthe(*t_h, *t_v);
        recupererDonneesLabyrinthe(fd, *t_h, *t_v, laby);

    }
    else{
        perror("Erreur durant la récupération des données du labyrinthe\n");
    }

    if (fclose(fd)==EOF){
        perror("Erreur dans la fermeture du fichier\n");
    }

    return laby;

}

void recupererDimensionLabyrinthe(FILE *fd, int *t_h, int *t_v){
    char line[15];
    if (fgets(line, sizeof(line), fd)!=NULL){
        *t_h=atoi(strtok(line,","));
        *t_v=atoi(strtok(line,","));
    }
    else{
        perror("Erreur dans la lecture de la première ligne du fichier \n");
    }
}

void recupererDonneesLabyrinthe(FILE *fd, int t_h, int t_v, Case **laby){
    char currentChar;
    int cpt_h=0, cpt_v=0;

    do{
        do{
            currentChar=fgetc(fd);
            switch(currentChar){
                case '#':
                case 'o':
                case 'X':
                case 'T':
                    laby[cpt_h][cpt_v].type=currentChar;
                    break;
                case ' ':
                    laby[cpt_h][cpt_v].type='v';
                    break;
                case '\n':
                    break;
                default:
                    perror("Error : caractère inconnu lors de la lecture du labyrinthe\n");
            }
            printf("%c", currentChar);
            cpt_h++;
        }while(currentChar != '\n');
        cpt_v++;
        cpt_h=0;
    } while (cpt_v<t_v);
}

void recupererTableauScore(Gagnant *tab_score, char *filename){
    FILE *fd=NULL;
    Gagnant current_g;
    char *chemin;
    char line[NB_CHAR_STRING+15];
    int cpt=0;

    sprintf(chemin,"./data/laby_score/%s.txt",filename);
    printf("Chemin du fichier : %s\n",chemin);
    fd=fopen(chemin,"r");
    if (fd!=NULL){
        while(fgets(line,sizeof(line),fd)!=NULL){
            current_g=recupererDonneesGagnant(line);
            tab_score[cpt]=current_g;
            cpt++;
            if(cpt>=NB_GAGNANT){
                break;
            }
        }
        if(cpt<NB_GAGNANT){
            while(cpt<NB_GAGNANT){
                tab_score[cpt].place=-1;
                sprintf(tab_score[cpt].nom_gagnant,"%s","");
                tab_score[cpt].score=-1;
                cpt++;
            }
        }
    }
    else{
        perror("Erreur d'ouverture lors de la récupération du tableau des scores");
    }
}

Gagnant recupererDonneesGagnant(char *line){
    Gagnant g;
    printf("==========\nConversion chaine -> Gagnant\n");
    printf("%s\n", line);

    sscanf(line, "%d %s %d",&g.place, g.nom_gagnant, &g.score);
    
    printf("%d\n", g.place);
    printf("%s\n", g.nom_gagnant);
    printf("%d\n", g.score);

    printf("FIN\n==========\n");

    return g;
}