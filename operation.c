#include <stdio.h>
#include <stdlib.h>
#include "operation.h"

#define ALPHA 0.85
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
                while (actuel != NULL)
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

double *initF(int nbr){

    double *f = calloc(nbr, sizeof(double));
    for(int i =0;i<nbr;i++){
        f[i]=1;
    }

    return f;

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


double  *convergence(Liste T[], int nbrelem, double *pi){

    double dif = 1;
    int iteration = 1;
    double *v1 = calloc(nbrelem, sizeof(double));
    double *v2 = calloc(nbrelem, sizeof(double));

     printf("Convergence Debut ! \n");

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

double *alphaP(double *p,int nbr){

     double *v1 = calloc(nbr, sizeof(double));

     for(int i =0 ;i<nbr;i++){
        v1[i]=p[i]*0.85;
     }

     return v1;
}

double *scalairE(double *pi,int nbr){

    double *f = calloc(nbr, sizeof(double));
    double *e = calloc(nbr, sizeof(double));
    f = initF(nbr);

    double scalair = 0;

    for(int i = 0;i<nbr;i++){
        scalair += pi[i]*f[i];
    }

    scalair = ALPHA*(1/nbr*1.0)*scalair;
    scalair += (1-ALPHA)*(1/nbr*1.0);

    for(int i =0 ;i<nbr;i++){
        e[i]=f[i]*scalair;
     }
    return e;

}



double *surferaleatoir(Liste T[], int nbrelem, double *pi)
{
    double dif = 1;
    int iteration = 1;
    double *v1 = calloc(nbrelem, sizeof(double));
    double *v2 = calloc(nbrelem, sizeof(double));

    multiplication(T,pi,v1,nbrelem);
    v2 = alphaP(v1,nbrelem);

}
