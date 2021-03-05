#include <stdlib.h>
#include <stdio.h>
#include <string.h>



typedef struct{
    int vertex1;  //destination du lien
    double weight; // probabilté de suivre ce lien
    struct EDGE *next; //prochain lien sur la meme page
}EDGE;

typedef EDGE *Liste;

Liste *initialisation();
Liste insertion(Liste *old, int sommetDep, double prob);
void afficherListe(Liste *liste,int i);
