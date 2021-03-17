#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"

void multiplication(Liste t[],double *pin, double *res, int nbrelem);
void initvect(double *vect,int nbrelem);
void affichervect(double *vect, int nbr);
double diff(double *A, double *B, int taille);
double *convergence (Liste t[],int nbrelem, double *pi);
double *initF(int nbr);
double *alphaP(Liste T[], double *p,int nbr);
double *scalairE(Liste T[],double *pi,double *ft,int nbr);
double *surferaleatoir(Liste T[], int nbrelem, double *pi,double *ft);
void remove_vertex(Liste T, int vertex_index);
