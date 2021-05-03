#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"
#include <time.h>
#include <math.h>

void multiplication(Liste t[],double *pin, double *res, int nbrelem);
void initvect(double *vect,int nbrelem);
void affichervect(double *vect, int nbr);
double diff(double *A, double *B, int taille);
double *convergence (Liste t[],int nbrelem, double *pi);
double *initF(int nbr);
double *alphaP(Liste T[], double *p,int nbr);
double *scalairE(Liste T[],double *pi,double *ft,int nbr);
double *surferaleatoir(Liste T[], int nbrelem, double *pi,double *ft);
void supprimerSommet(Liste T[], int nbrSommet, int nbVerticesToDelete, int *deletedVertices);
void initvect2(int *deletedVertices, double *oldVect, double *newVect, int nbrelem);
void normalise(double *vect, int nbelem);
void display_list(EDGE* list);
void display_matrix(EDGE** T, int nbrelem);
void ajuster_matrice_faster(EDGE **matrice, int *sommets_cibles, int size, int nbrelem, int *tableau_frequences, double *ft, double *conv, double *newPi);
int* generate_random_vector(int maximum, int size);
int findBound(int x, int* table, int size, int left, int right);
int isFound(int d, int* table, int size);
int decaler_matrice_faster(EDGE** matrice, int nbr_elements, int* deletion_vector, int dv_size);
int remove_vertex_faster(EDGE **matrice, int *sommets_cibles, int size, int nbrelem, double *conv, double *ft, double *newPi);
void generer_tableau_frequence(EDGE** matrice, int* tab, int size, int* deletion_vector);
