#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "operation.h"


int main(){

    // Start measuring time
    time_t begin, end;
    time(&begin);

    int nbrSommet , i, sommet1,sommet2, arc;
    long nbrArc;
    double poid;
    char chaine[1000000]="";
    FILE* fichier = NULL;

    double *pi;
    double *ft;
    double *res;
    char * pch1;

    sommet1 = 0;
    sommet2 = 0;
    poid = 0;
    arc = 0;



    fichier = fopen("web1.txt","r");
    if (fichier == NULL){
        printf("Impossible de lire le fichier !");
        exit(0);
    }


    fgets(chaine, 1000000, fichier); //prendre le premier element de notre fichier (matrice) c'est le nombre de sommets
    nbrSommet =atoi(chaine); // convertir le char en int en utilisant la fonction atoi

    fgets(chaine,1000000, fichier); // lire la deuxieme ligne (nombre d'arcs)
    nbrArc =atol(chaine); // convertir le char en long

    printf("le nombre de sommet : %d \n",nbrSommet);
    printf("le nombre d'arc : %ld \n",nbrArc);

    ft = calloc(nbrSommet, sizeof(double));


    EDGE** T = malloc(sizeof(EDGE*)* nbrSommet);// creer notre tableau de EDGE*


    for(i = 0;i<nbrSommet;i++){
        T[i]=initialisation();
    }


    while (fgets(chaine, sizeof(chaine), fichier) != NULL){ // On lit le fichier a partir de la 3 iem ligne tant qu'on ne reçoit pas d'erreur (NULL)
        // On cherche à récupérer, un à un, tous les mots  de la ligne i
        // et on commence par le premier.
        
        pch1 = strtok (chaine," ");
        sommet1 = atoi(pch1);// sommet i

        pch1 =strtok (NULL," ");//continue de "tokenizer" chaine
        arc = atoi(pch1);//nbr arc du sommet i

        //f vecteur ligne tq f(i)=1 si nb arc=0 et f(i)=0 sinon
        //ft vecteur colonne
        if(arc == 0)
            ft[sommet1-1]=1;
        else
            ft[sommet1-1]=0;

        //printf("le sommet : %d a %d successeur \n",sommet1,arc);
        while (pch1 != NULL ){

            // On demande le j ieme successeur.
            pch1 =strtok (NULL," ");

            if(pch1 != NULL){
                sommet2 = atoi(pch1);
            }

            // On demande le poids de l'arc vers j iem successeur.
            pch1 =strtok (NULL," ");

            if(pch1 != NULL){
                poid = atof(pch1);
                T[sommet2-1] = insertion(T[sommet2-1],sommet1,poid);
            }

        }

    }
    fclose(fichier);

    //afficherListe(T,nbrSommet); //AFFICHAGE

    pi = calloc(nbrSommet, sizeof(double));
    initvect(pi,nbrSommet);
    double *conv = calloc(nbrSommet, sizeof(double));
   // affichervect(pi,8);


    /*conv = convergence(T,nbrSommet,pi);       //TEST CONVERGENCE
    affichervect(conv,nbrSommet);*/

    /*multiplication(T,pi,conv,nbrSommet);
    double  *v1 =calloc(nbrSommet, sizeof(double));      //TEST ALPHA*M
    v1 = alphaP(conv,nbrSommet);
    affichervect(v1,nbrSommet);*/

    /*printf("Resultats surfer vecteur normal : \n");
    conv = surferaleatoir(T,nbrSommet,pi,ft);
    affichervect(conv,8);*/


    //1 if vertex deleted else 0
    int *deletedVertices = calloc(nbrSommet, sizeof(int));

    generateRandomVerticesToDelete(nbrSommet,8,deletedVertices);
    for (int i = 0; i < nbrSommet; i++){
        if (deletedVertices[i]==1){
            printf("Sommet %d a supprimer\n",i+1); 
        }
    }

    //supprime x sommets et modifie liste des sommets supprimés
    supprimerSommet(T, nbrSommet, deletedVertices);


    /*double *newVectInit = calloc(nbrSommet, sizeof(double));
    double *result = calloc(nbrSommet, sizeof(double));

    initvect2(deletedVertices, conv, newVectInit, nbrSommet);
    printf("Vector after initialising with previous vector : \n");
    affichervect(newVectInit,nbrSommet);

    normalise(newVectInit,nbrSommet);
    printf("Vector after normalising : \n");
    affichervect(newVectInit, nbrSommet);

    printf("Result :\n");
    result = surferaleatoir(T, nbrSommet, newVectInit, ft);
    affichervect(result,nbrSommet);*/

    // Stop measuring time and calculate elapsed time
    time(&end);
    time_t elapsed = end - begin;
    printf("Time measured: %ld seconds.\n", elapsed);

    free(ft);
    free(T);
    return 1;
}
