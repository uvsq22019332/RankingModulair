#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrice.h"


//j'ai remplacé liste par liste*
Liste initialisation(){
  Liste l = NULL;
  return l;
}


//j'ai remplacé Liste * old par Liste old
Liste insertion(Liste old, int sommetDep, double prob){
    EDGE *nouveau = malloc(sizeof(EDGE));

    nouveau->vertex1 = sommetDep;
    nouveau->weight = prob;
    nouveau->next = old;

    return nouveau;
}


//j'ai modifié l'affichage de la liste pour ne pas avoir de boucle dans le main
void afficherListe(Liste *liste,int nbrSommet){
    for (int i = 0; i < nbrSommet; i++){
        if (liste[i] == NULL){
            printf("Pas de predesseceur pour le sommet %d\n", i+1);
        }
        else{
            EDGE *actuel = liste[i];
            while (actuel != NULL){
                printf("%d==>%f==>%d  \n", actuel->vertex1, actuel->weight, i+1);
                actuel = actuel->next;
            }
        }
    }
}




void remplir_matrice_creuse(FILE* fichier, EDGE** T, int* vecteur_ft, int nbrSommet){

    char chaine[1000000];
    char* pch1;
    int sommet1;
    int arc;
    int nbrArc;
    int sommet2;
    double poid;


    // Extraction et conversion en int du nombre des arcs.
    fgets(chaine,1000000, fichier);
    nbrArc = atol(chaine);


    for( int i = 0; i < nbrSommet; i++ ){

        T[i] = initialisation();

    }   

    /*for ( int i = 0; i < nbrSommet; i++ ){

        printf("%d\n", T[i]);

    }*/

    printf("Nombre arcs : %d\n", nbrArc);

    
    while ( fgets(chaine, sizeof(chaine), fichier) != NULL ){


        // Tokenization de la première ligne et extraction du sommet concerné i et le nombre d'arcs entrant vers celui-ci
        pch1 = strtok(chaine," ");
        sommet1 = atoi(pch1);
        pch1 =strtok(NULL," ");
        arc = atoi(pch1);


        // Si il n'y a pas d'arcs entrant f[i] = 0 sinon, F[i] = 1
        if(arc == 0)
            vecteur_ft[sommet1-1]=1;

        while (pch1 != NULL ){

            // On demande le j ieme successeur.
            pch1 =strtok (NULL," ");

            if(pch1 != NULL){
                sommet2 = atoi(pch1);
            }

            // On demande le poids de l'arc vers j iem successeur.
            pch1 =strtok (NULL," ");

            if(pch1 != NULL){
                poid = atof(pch1);
                T[sommet2-1] = insertion(T[sommet2-1],sommet1,poid);
            }

        }

    }
    
    return;

}