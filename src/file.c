#include "../include/head.h"

void enregistrerLabyrinthe(int t_h, int t_v, Case **laby, char *filename){
    FILE *fd=NULL;
    int i,j;
    char chemin[NB_CHAR_FILE_NAME+9];

    sprintf(chemin,"data/%s.txt",filename);
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

        if (fclose(fd)==EOF){
            perror("Erreur dans la fermeture du fichier\n");
        }
    }
    
}

void recupererListeFichierRepertoire(char * repertoire, char **liste_fichier, int *len_liste){
    DIR *repo= opendir(repertoire);
    if (repo != NULL){
        struct dirent *red_dir;
        int len_filename;

        *len_liste=trouverNombreFichierDansRepertoire(repo);
        printf(">> %d fichiers trouvés \n", *len_liste);
        allouerMemoireListeFichier(*len_liste, liste_fichier);
        while (red_dir=readdir(repo)){
            len_filename=strlen(red_dir->d_name);
            if (len_filename>4){
                while (len_filename > 0 && red_dir->d_name[len_filename]!='.'){
                    len_filename--;
                }
                if (len_filename!=0){
                    red_dir->d_name[len_filename]='\0';
                }
                printf("%s\n", red_dir->d_name);
            }
        }
    }
    else{
        perror("Erreur dans l'affichage des fichiers d'un dossier\n");
    }
    closedir(repo);
}

void allouerMemoireListeFichier(int len_liste, char ** liste){
    int i;

    liste=(char **)malloc(len_liste*sizeof(char *));
    if (liste==NULL){
        printf("Erreur dans la création de la dimension principale du tableau\n");
    }    
    for(i=0;i<len_liste;i++){
        liste[i]=(char *)malloc(NB_CHAR_FILE_NAME*sizeof(char));
        if (liste[i]==NULL){
            int j;
            printf("Erreur dans la création du sous tableau %d \n",i);
            //si une erreur est survenue il faut liberer tout ce qui a déjà été alloué
            for(j=i-1;j>=0;j++){
                free(liste[j]);
            }
            free(liste);
        }
    }
}

void libererMemoireListeFichier(int len_liste, char ** liste){
    int i;

    for(i=0; i<len_liste; i++){
        free(liste[i]);
    }
    free(liste);
}

int trouverNombreFichierDansRepertoire(DIR *repo){
    int nb_file=0;
    struct dirent *red_dir;
    while (red_dir=readdir(repo)){
        nb_file++;
    }
    return nb_file-2; // pour ne pas compter . et .. qui ne sont pas des fichiers
}