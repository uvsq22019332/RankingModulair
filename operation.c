#include <stdio.h>
#include <stdlib.h>
#include "operation.h"

#define EPSILON 0.000001
#define ABS(x) (((x) < 0) ? -(x) : (x))



void multiplication(Liste t[] , double *pi, double *res, int nbr)
{

    for(int i = 0 ;i<nbr;i++){
            double multi = 0;

            if (t[i] == NULL)
            {
                res[i]=0;

            }else{
                EDGE *actuel = t[i];
                while (actuel != NULL && actuel->vertex1 != 0)
                {
                    multi = multi+(pi[actuel->vertex1-1]*actuel->weight);
                    actuel = actuel->next;
                }
                res[i]= multi;
            }
    }
    return res;
}



void initvect(double *vect,int nbrelem){
    int i = 0 ;
    for(i =0;i<nbrelem;i++){
        vect[i]= 1.0/(nbrelem*1.0);
    }

}

double *renit(double *vect,int nbr){
    int i;
    for(i =0;i<nbr;i++){
        vect[i]=0;
    }

    return vect;

}

void affichervect(double *vect,int nbr){
    int i;

    for(i=0;i<nbr;i++){
        printf("%lg \t",vect[i]);
    }
    printf("\n");
}

//Difference entre deux vecteurs
double diff(double *A, double *B, int taille) {
	double diff = 0;
	for(int i = 0; i < taille; i++) {
		diff += ABS(A[i]-B[i]);
	}
	return diff;
}

double *affectation(double *A,double *B, int nbr){

    for(int i = 0;i>nbr;i++){
        A[i]=B[i];
    }
    return A;

}

double  *convergence(Liste T[], int nbrelem, double *pi, double *conv){

    double dif = 1;
    int iteration = 1;
    double *v1 = calloc(nbrelem, sizeof(double));
    double *v2 = calloc(nbrelem, sizeof(double));

    multiplication(T,pi,v1,nbrelem);
    dif =diff(pi,v1,nbrelem);

    while (dif > EPSILON){

        multiplication(T,v1,v2,nbrelem);
        dif =diff(v1,v2,nbrelem);
        printf("%lg \n",dif);
        free(v1);
        v1 = v2;
        v2 = calloc(nbrelem, sizeof(double));
        iteration++;
        printf("nombre d'iteration %d \n",iteration);
    }
        printf("FIN ! \n");




    return v1;


}
