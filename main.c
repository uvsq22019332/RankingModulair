#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "operation.h"


int main(int argc, char *argv[]){

    // Start measuring time
    time_t begin, end;
    time(&begin);

    int nbrSommet , i, sommet1,sommet2, arc;
    long nbrArc;
    double poid;
    char chaine[1000000]="";
    FILE* fichier = NULL;

    double *pi;
    double *ft;
    char * pch1;
    double* conv;
    double* conv2;

    char* percent = argv[2];
    int percent_integer;

    sommet1 = 0;
    sommet2 = 0;
    poid = 0;
    arc = 0;


    char * graphFile = argv[1];
    printf("Fichier %s\n",graphFile);
    fichier = fopen(graphFile,"r");
    if (fichier == NULL){
        printf("Impossible de lire le fichier !");
        exit(0);
    }

    // Lecture de la première ligne qui représente le nombre de sommet du graphe et conversion de cette valeur en int.
    fgets(chaine, 1000000, fichier);
    nbrSommet =atoi(chaine); 

    // Lecture de la deuxième ligne, représente le nombre d'arcs. [Pas besoin d'un long ? un int normal peut prendre plus que 2 milliard de valeurs]
    fgets(chaine,1000000, fichier); 
    nbrArc =atol(chaine);


    printf("le nombre de sommet : %d \n",nbrSommet);
    printf("le nombre d'arc : %ld \n",nbrArc);
    printf("\n \n");
    
    // Allocation + Initialisation à 0 du vecteur ft.
    ft = calloc(nbrSommet, sizeof(double));


    // Déclaration d'un tableau de pointeur vers EDGE.
    EDGE** T = malloc(sizeof(EDGE*)* nbrSommet);


    // Initialisation du tableau de pointeur vers EDGE a null pour chaque case.
    for(i = 0;i<nbrSommet;i++){
         T[i]=initialisation();
    }

    // On lit le fichier a partir de la 3ème ligne tant qu'on ne reçoit pas d'erreur (NULL)
    // On cherche à récupérer, un à un, tous les mots  de la ligne i
    while (fgets(chaine, sizeof(chaine), fichier) != NULL){

        // Extraction du premier token de la chaine recue, il représente le sommet d'origine.
        pch1 = strtok (chaine," "); 
        sommet1 = atoi(pch1);

        // Extraction du deuxième token de la chaine recue, il représente le nombre d'arc sortants de l'origine
        pch1 =strtok (NULL," ");
        arc = atoi(pch1);

        // Mise à jour du vecteur ligne ft. Si l'origine a des arcs sortants, sa valeur correspondante dans ft est mise à 0, sinon 1.
        if(arc == 0)
            ft[sommet1-1]= 1;
        else
            ft[sommet1-1]= 0;

        //printf("le sommet : %d a %d successeur \n",sommet1,arc);

        // La variable pch1 garantie l'execution du corps de la boucle au moins une première fois.
        while ( pch1 != NULL ){

            // On demande le j ieme successeur.
            pch1 =strtok (NULL," ");

            // Si il existe bien un successeur, on récupère sa valeur.
            if(pch1 != NULL){
                sommet2 = atoi(pch1);
            }

            // On demande le poids de l'arc vers j iem successeur.
            pch1 =strtok (NULL," ");

            // Si il existe bien un poids ? on récupère sa valeur et on insère dans le tableau des pointeurs vers EDGE
            if(pch1 != NULL){
                poid = atof(pch1);
                T[sommet2-1] = insertion(T[sommet2-1],sommet1,poid);
            }

        }

    }

    fclose(fichier);






    // ##################### Convergence surfer aléatoire pour le graphe initial ##############################

    pi = calloc(sizeof(double), nbrSommet);

    display_matrix(T, nbrSommet);

    initvect(pi, nbrSommet);

    conv = surferaleatoir(T, nbrSommet, pi, ft);

    affichervect(conv, nbrSommet);


    // #########################################################################################################









    // ##################### Suppression d'un pourcentage de sommets et d'arcs #################################

    percent_integer = nbrSommet*(atof(percent)/100);

    int* vecteur_suppression = malloc(sizeof(int) * percent_integer);
    double* newPi = malloc((nbrSommet - percent_integer) * sizeof(double));

    //display_matrix(T, nbrSommet);
    printf("\n\n\n");

    // Génération du vecteur de suppression
    vecteur_suppression = generate_random_vector(nbrSommet, percent_integer);
    for (int i = 0; i < percent_integer; i++){

        printf("%d ", vecteur_suppression[i]);

    }
    printf("\n\n\n");

    // Suppression
    T = remove_vertex_faster(T, vecteur_suppression, percent_integer, nbrSommet, ft, conv, newPi);
    nbrSommet = nbrSommet - percent_integer;
    display_matrix(T, nbrSommet);

    affichervect(newPi, nbrSommet);

    exit(0);
    // ############################################################################################################







    // ##################### Convergence surfer aléatoire pour le graphe modifié ################################

    // Ajustement du vecteur de pertinence
    pi = realloc(pi, sizeof(double) * nbrSommet);
    initvect(pi, nbrSommet);

    // Déclaration du nouvel vecteur de pertinence
    conv2 = surferaleatoir(T, nbrSommet, pi, ft);
    affichervect(conv2, nbrSommet);

    // ############################################################################################################







    // ############## Convergence surfer aléatoire pour le graphe modifié en utilisant l'ancien vecteur de pertinence ##################

    // Initialisation du vecteur de pertinence avec les anciens valeurs







    /*printf("Matrice apres supression des sommets\n");
    display_matrix(T, nbrSommet);
    printf("\n\n\n");*/



    exit(0);

    /*
    //ouverture/creation du fichier csv
    FILE *fpt;
    graphFile[strlen(graphFile) - 4] = 0;
    char fileName[50] = "results_";
    strcat(fileName,graphFile);
    strcat(fileName,".csv");
    fpt = fopen(fileName, "w+");


    printf("Matrice avant supression :\n");
    display_matrix(T, nbrSommet);
    printf("\n \n");

    // Allocation du vecteur de convergence
    double *conv = calloc(nbrSommet, sizeof(double));
    
    //Allocation du 2ème vecteur de pertinence qui sera initialisé avec les anciennes valeurs de pi
    double *newPi = calloc(nbrSommet, sizeof(double));

    // Allocation + Initialisation du vecteur des pertinences
    pi = calloc(nbrSommet, sizeof(double));
    initvect(pi,nbrSommet);
    printf("Vecteur Pi : \n");
    affichervect(pi,nbrSommet);
    printf("\n \n");

    // Convergence surfer aléatoire graphe initial
    conv = surferaleatoir(T,nbrSommet,pi,ft); 
    double * savedConv = conv;
    printf("Valeurs de convergence surfer aleatoire pour le vecteur Pi : \n");
    affichervect(conv,nbrSommet);
    printf("\n \n");
    

    //sauvegarde du resultat dans fichier csv
    for(int i=0; i<nbrSommet;i++){
        fprintf(fpt, "%f;", conv[i]);
    }
    fprintf(fpt,"\n");
    
    //pourcentage de sommets supprimés
   /* 
    int size = nbrSommet*(atof(percent)/100);*/

    //suppression
  /*  int *tab = generate_random_vector(nbrSommet,size);
    for(int i=0;i<size;i++){
        printf("tab[%d]=%d\n",i,tab[i]);
    }*/

    /*int tab[2]={4,6};
    nbrSommet = remove_vertex_faster(T , tab, 2, nbrSommet,savedConv,ft,newPi);
    printf("Matrice apres supression des sommets\n");
    display_matrix(T, nbrSommet);
    printf("\n\n");


    // Convergence surfer aléatoire graphe modifié
    double *conv2 = calloc(nbrSommet, sizeof(double));
    double*pi2 = calloc(nbrSommet, sizeof(double));
    initvect(pi,nbrSommet);
    conv2 = surferaleatoir(T,nbrSommet,pi2,ft); 
    printf("Valeurs de pi :\n");
    affichervect(pi,nbrSommet );
    printf("Valeurs de convergence surfer aleatoire pour le vecteur Pi apres suppression: \n");
    affichervect(conv2,nbrSommet);
    printf("\n \n");

    printf("Vecteur pi initialisé avec les resulats précédents (avant normalisation)\n");
    affichervect(newPi, nbrSommet);

    //save in csv file
    for (int i = 0; i < nbrSommet; i++)
    {
        fprintf(fpt, "%f;", conv2[i]);
    }
    fprintf(fpt, "\n");

    //Normalisation newPi
    normalise(newPi, nbrSommet);

    //Convergence en initialisant avec l'ancien vecteur
    conv2 = surferaleatoir(T, nbrSommet, newPi, ft);
    printf("Vecteur pi initialisé avec les resulats précédents (après normalisation)\n");
    affichervect(newPi, nbrSommet);
    printf("\n \n");

    printf("Valeurs de convergence surfer aleatoire pour le vecteur Pi apres suppression et init avec anciens resultats: \n");
    affichervect(conv2, nbrSommet);
    printf("\n \n");

    //save in csv file
    for (int i = 0; i < nbrSommet; i++)
    {
        fprintf(fpt, "%f;", conv2[i]);
    }
    fprintf(fpt, "\n");

    //Stop measuring time and calculate elapsed time
    time(&end);
    time_t elapsed = end - begin;
    printf("Time measured: %ld seconds.\n", elapsed);
    */
    free(ft);
    free(T);
    
    return 1;
}
