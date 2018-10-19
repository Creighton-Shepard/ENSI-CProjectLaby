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

char ** recupererListeFichierRepertoire(char * repertoire, int *len_liste){
    char ** liste_fichier;
    *len_liste=trouverNombreFichierDansRepertoire(repertoire);
    printf(">> %d fichiers trouvés \n", *len_liste);
    if (*len_liste>=0){
        DIR *repo= opendir(repertoire);
        if (repo != NULL){
            struct dirent *red_dir;
            int len_filename;
            int cpt=0;
 
            liste_fichier=allouerMemoireListeFichier(*len_liste);
        
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
    else{
        printf("Pas de fichiers disponible ! Veuillez créer de nouveaux labyrinthe !\n");
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

    recupererDimensionLabyrinthe(filename, t_h, t_v);

    laby=allouerMemoireLabyrinthe();
}

void recupererDimensionLabyrinthe(char *filename, int *t_h, int *t_v){

}