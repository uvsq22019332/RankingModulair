#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "operation.h"

#define ALPHA 0.85
#define EPSILON 0.000001
#define ABS(x) (((x) < 0) ? -(x) : (x))



void multiplication(Liste t[] , double *pi, double *res, int nbr){

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

double *surferaleatoir(Liste T[], int nbrelem, double *pi,double *ft){
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

void supprimerSommet(Liste T[], int nbrSommet, int nbVerticesToDelete, int *deletedVertices){

    /*printf("\nGraphe avant modifications\n");
    printf("----------------------------------\n");
    afficherListe(T, nbrSommet);
    printf("----------------------------------\n");*/

    //On vérifie que le nombre de sommets à supprimer défini est bien inférieur au nombre de sommets total
    if(nbVerticesToDelete>nbrSommet){
        printf("Le nombre de sommets a supprimer est superieur au nombre de sommets");
        exit(0);
    }

    //seed for random generator 
    srand(time(NULL));

    int i, k, upper, lower, randVertex, oldRand, counter;
    counter = 0;
    oldRand = 0;
    lower = 1;
    upper = nbrSommet;

    //On supprime un nombre de sommets aléatoires défini par nbVerticesToDelete
    for (k = 0; k < nbVerticesToDelete; k++){

        //on génère un sommet aléatoire en ne tirant pas 2 fois le même sommet
        randVertex = (rand() % (upper - lower + 1)) + lower;
        while (deletedVertices[randVertex - 1]==1){
            randVertex = (rand() % (upper - lower + 1)) + lower;
        }            
    
        //printf("---------Vertex to delete = %d---------\n", randVertex);

        //suppression predecesseurs du sommet à supprimer
        T[randVertex - 1] = NULL;

        //on met à 1 si le sommet a été supprimé
        deletedVertices[randVertex - 1] = 1;

        //Parcours tableau
        for (i = 0; i < nbrSommet; i++){

            EDGE *actuel = T[i];
            EDGE *suivant;
            if (actuel != NULL){
                suivant = actuel->next;
            }
            else{
                continue;
            }
            counter = 0;

            while (actuel != NULL){
                //printf("Sommet actuel : %d\n",actuel->vertex1);

                //si le sommet à supprimer est en tête de liste
                if (actuel->vertex1 == randVertex && counter == 0){
                    // printf("Sommet a supprimer en tete de liste\n");
                    T[i] = actuel->next;
                    free(actuel);
                    break;
                }
                //sommet à supprimer en milieu de liste
                else if (suivant != NULL && suivant->vertex1 == randVertex){
                    // printf("Sommet a supprimer dans la liste\n");
                    actuel->next = suivant->next;
                    free(suivant);
                    break;
                }
                actuel = actuel->next;
                counter++;
            }
        }
    
    }

    printf("%d sommet(s) supprime(s)\n",nbVerticesToDelete);

    /* printf("\nGraphe apres modifications\n");
    printf("----------------------------------\n");
    afficherListe(T, nbrSommet);*/

}

void initvect2(int *deletedVertices, double * oldVect, double *newVect, int nbrelem){
    int i = 0;

    for (i = 0; i < nbrelem; i++){
        //Si le sommet n'a pas été supprimé on initialise avec l'ancien résultat 
        if(deletedVertices[i]==0){
            newVect[i] = oldVect[i];
        }
        //sinon on initialise a 1/N
        else{
            newVect[i] = 1.0 / (nbrelem * 1.0);
        }
    }
}

void normalise(double *vect, int nbelem){
    double somme = 0;
    for (int i = 0; i <nbelem; i++)
    {
        somme += vect[i];
    }
    for (int i = 0; i < nbelem; i++){
        vect[i] /= somme;
    }
}