#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrice.h"



Liste *initialisation(){
  Liste *l = NULL;
  return l;
}




Liste insertion(Liste *old, int sommetDep, double prob){
    EDGE *nouveau = malloc(sizeof(EDGE));

    nouveau->vertex1 = sommetDep;
    nouveau->weight = prob;
    nouveau->next = old;

    return nouveau;

}




void afficherListe(Liste *liste,int i){

    if (liste == NULL)
    {
        printf("pas de predesseceur pour le sommet %d\n",i);
    }else{

            EDGE *actuel = liste;

            while (actuel != NULL){
                    printf("%d==>%f==>%d  \n",actuel->vertex1,actuel->weight,i);
                    actuel = actuel->next;
            }
    }



}
