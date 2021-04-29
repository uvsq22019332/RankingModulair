#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrice.h"


Liste initialisation(){
  Liste l = NULL;
  return l;
}

// Prend l'ancien adresse de la tete d'une liste, une probabilité de routage et son origine
// Crée -En utilisant les paramètres- et insert un nouveau EDGE dans la tete de la liste et renvoi son adresse en étant la nouvelle tete de liste.
Liste insertion(Liste old, int sommetDep, double prob){
    EDGE *nouveau = malloc(sizeof(EDGE));

    nouveau->vertex1 = sommetDep;
    nouveau->weight = prob;
    nouveau->next = old;

    return nouveau;
}



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
