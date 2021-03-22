#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "operation.h"


int main(){

    // Start measuring time
    time_t begin, end;
    time(&begin);

    FILE* fichier;
    double *pi;
    double *res;
    int* ft;
    int nbrSommet;
    char chaine[1];

    // Ouverture du fichier.
    fichier = open_file("web1.txt", "r");

    // Extraction du nombre de sommets.
    fgets(chaine, 1000000, fichier);
    nbrSommet = atoi(chaine);

    // Allocation mémoire au vecteur ft et à la matrice creuse de proba en utilisant le nombre de sommets extrait.
    EDGE** T = malloc(sizeof(EDGE*) * nbrSommet);
    ft = calloc(nbrSommet, sizeof(int));

    // Lecture et remplissage de la matrice creuse + setup du vecteur ft.
    remplir_matrice_creuse(fichier, T, ft, nbrSommet);


    fclose(fichier);
    afficherListe(T,8); //AFFICHAGE

    remove_vertex(T, 3, nbrSommet);

    printf("\n");
    afficherListe(T,8);

    return 0;
    // Allocation de la mémoire et initiation du vecteur de pertinence PI.
    pi = calloc(nbrSommet, sizeof(double));
    initvect(pi,nbrSommet);
    affichervect(pi,8);

    // Convergence surfer aléatoire
    double *conv = calloc(nbrSommet, sizeof(double));
    conv = surferaleatoir(T,nbrSommet,pi,ft);

    affichervect(conv,8);

    // Stop measuring time and calculate elapsed time
    time(&end);
    time_t elapsed = end - begin;
    printf("Time measured: %ld seconds.\n", elapsed);


    free(ft);
    free(T);




    return 1; 
}
