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
    //return res;
}


//initialise le vecteur des pertinences 
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

double *alphaP(Liste T[],double *pi,int nbr){

     double *v1 = calloc(nbr, sizeof(double));
     double *v2 = calloc(nbr, sizeof(double));

     multiplication(T,pi,v1,nbr);

     for(int i =0 ;i<nbr;i++){
        v2[i]=v1[i]*0.85;
     }

     return v2;
}

double *scalairE(Liste T[],double *pi,double *ft,int nbr){

    double *e = calloc(nbr, sizeof(double));
    double *E = calloc(nbr, sizeof(double));

    e= initF(nbr);


    double scalair = 0;

    double s1,s2,s3;


    s3=0;

    double N = (nbr*1.0);



    for(int i = 0;i<nbr;i++){
        s3 += pi[i]*ft[i];
    }

    s1 = (1-0.85)*(1/N);
    s2=0.85*(1/N);
    s2*=s3;


    scalair = s1+s2;

    for(int i =0 ;i<nbr;i++){
        E[i]=e[i]*scalair;
     }
    return E;

}

double *AdditionVect(double *xp, double *xfe, int nbr){

    double *v1 = calloc(nbr, sizeof(double));

    for(int i = 0;i<nbr;i++){
        v1[i]=xp[i]+xfe[i];
    }
    return v1;
}

double *surferaleatoir(Liste T[], int nbrelem, double *pi,double *ft)
{
    double dif = 0;
    int iteration = 1;
    double *xp = calloc(nbrelem, sizeof(double));
    double *xfe = calloc(nbrelem, sizeof(double));
    double *x = calloc(nbrelem, sizeof(double));
    double *x2 = calloc(nbrelem, sizeof(double));

    xp = alphaP(T,pi,nbrelem);
    xfe = scalairE(T,pi,ft,nbrelem);
    x = AdditionVect(xp,xfe,nbrelem); //c'est xG
    dif = diff(x,pi,nbrelem);

    free(xp);
    free(xfe);

    while (dif>EPSILON){
            xp = calloc(nbrelem, sizeof(double));
            xfe = calloc(nbrelem, sizeof(double));
            xp = alphaP(T,x,nbrelem);
            xfe = scalairE(T,x,ft,nbrelem);
            x2 = AdditionVect(xp,xfe,nbrelem); //c'est xG
            dif = diff(x,x2,nbrelem);
            free(x);
            free(xp);
            free(xfe);
            x=x2;
            x2 = calloc(nbrelem, sizeof(double));
            iteration++;   
    }
    //affichervect(x, 8);

    printf("nombre d'iteration est %d \n",iteration);
    return x;
}




void remove_vertex(Liste T, int vertex_index, int nb_sommets){

    for (int i = 0; i < nb_sommets; i++){

        EDGE walking_node = T[i];
        EDGE save_the_next;

        // Si on tombe sur la ligne des arcs entrant du sommet, on supprime tout, comme le sommet ne doit plus exister.
        if ( i == vertex_index ){

            while ( walking_node != NULL ){
                
                save_the_next = walking_node->next;
                free(walking_node);
                walking_node = save_the_next;

            }

        }

        // Si une ligne ne contient qu'un seul arc et celui-ci est entrant depuis vertex_index, on supprime la liste. [cas spécial]
        if ( walking_node->next == NULL && walking_node->vertex1 = vertex_index){

            free(walking_node);
            T[i] = NULL;

        }

        // Si une ligne contient un arc entrant depuis vertex_index, on le supprime.
        while ( walking_node != NULL ){

            if ( walking_node->next->vertex1 == vertex_index ){
                
                save_the_next = walking_node->next->next;
                free(walking_node->next);
                walking_node->next = save_the_next;

            }

        }

    }

}