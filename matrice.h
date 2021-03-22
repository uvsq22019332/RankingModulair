#include <stdlib.h>
#include <stdio.h>
#include <string.h>



typedef struct EDGE EDGE;
struct EDGE{
    int vertex1;  //destination du lien
    double weight; // probabilité de suivre ce lien
    struct EDGE *next; //prochain lien sur la meme page
};

typedef EDGE *Liste;


Liste initialisation();//j'ai remplacé Liste par Liste*
Liste insertion(Liste old, int sommetDep, double prob); //j'ai remplacé Liste * old par Liste old
void afficherListe(Liste *liste, int nbrSommet);
void remplir_matrice_creuse(FILE* file_descriptor, EDGE** matrice, int* vecteur_ft, int nbrSommet);