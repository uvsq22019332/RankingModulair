#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "operation.h"


int main(){

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
    double *res;
    char * pch1;

    sommet1 = 0;
    sommet2 = 0;
    poid = 0;
    arc = 0;



    fichier = fopen("web1.txt","r");
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

    // Allocation du vecteur de convergence
    double *conv = calloc(nbrSommet, sizeof(double));

    // Allocation + Initialisation du vecteur des pertinences
    pi = calloc(nbrSommet, sizeof(double));
    initvect(pi,nbrSommet);

    // Convergence normale, sans surfer aléatoire
    conv = convergence(T,nbrSommet,pi); 
    printf("Valeurs de convergence normale pour le vecteur Pi : \n");
    affichervect(conv,8);
    printf("\n \n");


    int tab[1] = {7};
    nbrSommet = remove_vertex_faster(T , tab, 1, nbrSommet, pi);
    printf("Yeah : %d\n", nbrSommet);
    display_matrix(T, nbrSommet);
    printf("\n\n");


    // Réalloation 
    conv = realloc(conv, nbrSommet * sizeof(double));

    // Convergence normale, sans surfer aléatoire
    conv = convergence(T,nbrSommet,pi); 
    printf("EAEAZEAAZEA");
    printf("Valeurs de convergence normale pour le vecteur Pi : \n");
    affichervect(conv,7);
    printf("\n \n");

    


    // Suppression d'un sommet
    /*for (int i = 1; i < 10000; i++ ){
        nbrSommet = remove_vertex(i, T, pi, nbrSommet);
        printf("Nombre de sommets : %d\n", nbrSommet);
    }*/
    

    //display_matrix(T, nbrSommet);


    // reallocation du vecteur de convergence
    //conv = (double*) realloc(conv, nbrSommet * sizeof(double));

    // Convergence normale, sans surfer aléatoire
    //conv = convergence(T, nbrSommet, pi); 
    //printf("Valeurs de convergence normale pour le vecteur Pi : \n");
    //affichervect(conv,7);
    //printf("\n \n");

    /*
    printf("Initialisation du vecteur des pertinences Pi donne : \n");
    affichervect(pi,7);
    printf("\n \n");

    // Allocation du vecteur de convergence
    double *conv = calloc(nbrSommet, sizeof(double));

    // Convergence normale, sans surfer aléatoire
    conv = convergence(T,nbrSommet,pi); 
    printf("Valeurs de convergence normale pour le vecteur Pi : \n");
    affichervect(conv,7);
    printf("\n \n");

    // /*multiplication(T,pi,conv,nbrSommet);
    // double  *v1 =calloc(nbrSommet, sizeof(double));      //TEST ALPHA*M
    // v1 = alphaP(conv,nbrSommet);
    // affichervect(v1,nbrSommet);*/

    // Convergence surfer aléatoire
    printf("Valeurs de convergence surfer aléatoire pour le vecteur Pi : \n");
    conv = realloc(conv, nbrSommet * sizeof(double));
    conv = surferaleatoir(T,nbrSommet,pi,ft);
    affichervect(conv,7);

    // //1 if vertex deleted else 0
    // int *deletedVertices = calloc(nbrSommet, sizeof(int));

    // //supprime x sommets et modifie liste des sommets supprimés
    // supprimerSommet(T, nbrSommet, 1, deletedVertices);

    // double *newVectInit = calloc(nbrSommet, sizeof(double));
    // double *result = calloc(nbrSommet, sizeof(double));

    // initvect2(deletedVertices, conv, newVectInit, nbrSommet);
    // printf("Vector after initialising with previous vector : \n");
    // affichervect(newVectInit,nbrSommet);

    // normalise(newVectInit,nbrSommet);
    // printf("Vector after normalising : \n");
    // affichervect(newVectInit, nbrSommet);

    // printf("Result :\n");
    // result = surferaleatoir(T, nbrSommet, newVectInit, ft);
    // affichervect(result,nbrSommet);

    // // Stop measuring time and calculate elapsed time
    // time(&end);
    // time_t elapsed = end - begin;
    // printf("Time measured: %ld seconds.\n", elapsed);

    // free(ft);
    // free(T); */
    
    return 1;
}
