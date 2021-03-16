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
