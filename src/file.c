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