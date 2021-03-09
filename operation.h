#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"

void multiplication(Liste t[],double *pin, double *res, int nbrelem);
void initvect(double *vect,int nbrelem);
void affichervect(double *vect, int nbr);
double diff(double *A, double *B, int taille);
double *convergence (Liste t[],int nbrelem, double *pi, double *conv);
double *renit(double *vect,int nbr);
