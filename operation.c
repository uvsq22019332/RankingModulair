#include <stdio.h>
#include <stdlib.h>
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
        printf("%.19lf \t",vect[i]);
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


    multiplication(T,pi,v1,nbrelem);
    dif =diff(pi,v1,nbrelem);

    while (dif > EPSILON){

        multiplication(T,v1,v2,nbrelem);
        dif =diff(v1,v2,nbrelem);
        free(v1);
        v1 = v2;
        v2 = calloc(nbrelem, sizeof(double));
        iteration++;
        
    }
    
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

    // alpha * pi * T + [(1 - alpha)(1 / nbelem) + alpha(1 / nbelem)(pi * ft)]e

    double *e = calloc(nbr, sizeof(double));
    double *E = calloc(nbr, sizeof(double));

    // Initialise le vecteur e à 1.
    e= initF(nbr);


    double scalair = 0;
    double s1,s2,s3;

    s3=0;

    double N = (nbr*1.0);

    // Calcule du scalair pi * ft
    for(int i = 0;i<nbr;i++){
        s3 += pi[i]*ft[i];
    }

    // Calcule de (1 - alpha)(1/nbelem)
    s1 = (1-0.85)*(1/N);

    // Calcule de alpha*(1/N)
    s2=0.85*(1/N);

    // Calcule de (alpha*(1/N)) * (pi * ft)
    s2*=s3;

    // scalair contient : [(1 - alpha)(1 / nbelem) + alpha(1 / nbelem)(pi * ft)]
    scalair = s1+s2;


    for(int i =0 ;i<nbr;i++){
        // Pas besoin de faire ca, e est un vecteur ligne qui ne contient que des 1
        // Il sert à convertir un scalair à un vecteur ligne
        // Sans stocker e, on peut juste mettre le scalair dans chaque case de E[i] directement.
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

    // alpha * pi * T + [(1 - alpha)(1 / nbelem) + alpha(1 / nbelem)(pi * ft)]e
    double dif = 0;
    int iteration = 1;
    double *xp = calloc(nbrelem, sizeof(double));
    double *xfe = calloc(nbrelem, sizeof(double));
    double *x = calloc(nbrelem, sizeof(double));
    double *x2 = calloc(nbrelem, sizeof(double));

    // Calcule de alpha * pi * T - Checked
    xp = alphaP(T,pi,nbrelem);

    // Calcule [(1 - alpha)(1 / nbelem) + alpha(1 / nbelem)(pi * ft)]e
    xfe = scalairE(T,pi,ft,nbrelem);
    

    // Calcule alpha * pi * T + [(1 - alpha)(1 / nbelem) + alpha(1 / nbelem)(pi * ft)]e
    x = AdditionVect(xp,xfe,nbrelem); 

    dif = diff(x,pi,nbrelem);

    free(xp);
    free(xfe);

    while (dif>EPSILON){

            xp = calloc(nbrelem, sizeof(double));
            xfe = calloc(nbrelem, sizeof(double));

            xp = alphaP(T,x,nbrelem);
            xfe = scalairE(T,x,ft,nbrelem);
            x2 = AdditionVect(xp,xfe,nbrelem);

            dif = diff(x,x2,nbrelem);

            free(x);
            free(xp);
            free(xfe);

            x=x2;
            x2 = calloc(nbrelem, sizeof(double));
            iteration++;
    }
    

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

        //suppression successeur du sommet à supprimer
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



void display_list(EDGE* list){

    EDGE* traversal_pointer = list;

    while ( traversal_pointer != NULL ){
        
        printf("%d ",traversal_pointer->vertex1);
        traversal_pointer = traversal_pointer->next;

    }
    printf("\n");

}


void display_matrix(EDGE** T, int nbrelem){

    EDGE* traversal_node;

    for (int i = 0; i < nbrelem; i++){

        traversal_node = T[i];
        printf("%d [Sommet : %d] : ", i, i+1);

        if ( traversal_node == NULL ){

            printf("%s","Sommet sans predecesseurs");

        }

        while ( traversal_node ){

            printf("--> %d : %lf ", traversal_node->vertex1, traversal_node->weight);
            traversal_node = traversal_node->next;

        }
        printf("\n");
    }
    
}

                ////// ######################################## Gestion de suppression commance ici ###################################### //////


// Renvoi 1 si l'element d se retrouve dans le tableau, 0 sinon.
int isFound(int d, int* table, int size){

    for (int i = 0; i < size; i++){

        if ( d == table[i]){
            return 1;
        }

    }

    return 0;
}


// Génère un tableau de nombre aléatoire pré-trié
int* generate_random_vector(int maximum, int size){

    int* vector = malloc((size + 1) * sizeof(int));
    int prob = maximum;
    int disturbance = 0;
    int counter = 0;
    srand( time( NULL ) );

    for (int i = 1; i <= maximum; i++){

        prob = rand()%100;
        
        if ( prob < (((size/(double)maximum)*100) + disturbance) ){
            
            vector[counter] = i;
            counter++;

            if ( counter == size ){
                break;
            }
        }

        if ( i == ((maximum - size) - 1) ){
                disturbance = 100;
        }

    }
    
    return vector;

}


// Trouve la borne supérieur de l'element x
int findBound(int x, int* table, int size, int left, int right){

    
    int m = ((left + right) / 2);

    if ( x == table[m]){

        return m + 1;
        
    }

    if ( x < table[0] ){

        return 0;

    }

    if ( x > table[size-1]){

        return size;

    }

    if ( right == left + 1 ){

        return right;

    } 

    if ( table[m] > x ){

        right = m;

    }

    if ( table[m] < x ){

        left = m;

    }


    return findBound(x, table, size, left, right);

}

// Décale la matrice
int decaler_matrice_faster(EDGE** matrice, int nbr_elements, int* deletion_vector, int dv_size){


    int i = 1;
    int bound = 0;

    while ( i < nbr_elements ){

        bound = findBound(i, deletion_vector, dv_size, 0, (dv_size-1) );


        while ( isFound(i, deletion_vector, dv_size) ){

            matrice[i - bound] =  matrice[i];
            if ( isFound(i+1, deletion_vector, dv_size ) ){
                bound++;
            }
            i++;

            

        }

        while ( !isFound(i, deletion_vector, dv_size) && i < nbr_elements ){

            matrice[i - bound] =  matrice[i];
            i++;
        }

    }

    return nbr_elements - dv_size;

}

// Enlève un groupe de sommets et ajuste la matrice [ Principale ]
int remove_vertex_faster(EDGE **matrice, int *sommets_cibles, int size, int nbrelem, double *conv, double *ft, double *newPi)
{

    int* tableau_frequences = calloc((nbrelem+1), sizeof(int));

    // Génératino du tableau de frequence.
    generer_tableau_frequence(matrice, tableau_frequences, size, sommets_cibles);

    // Suppression
    nbrelem = decaler_matrice_faster(matrice, nbrelem, sommets_cibles, size);

    // Ajustement de la matrice
    ajuster_matrice_faster(matrice, sommets_cibles, size, nbrelem, tableau_frequences, ft, conv,newPi);

    // Ajustement du vecteur de pertinence
    //initvect(pi, nbrelem);

    /*for (int i = 0; i < (nbrelem - 1); i++){

        pi[i] = pi[i + 1];

    }*/

    return nbrelem;
}

// Génère un tableau de frequence à partir d'un tableau d'entier 
void generer_tableau_frequence(EDGE** matrice, int* tab, int size, int* deletion_vector){

    for (int i = 0; i < size; i++){

        EDGE* traversal_node = matrice[deletion_vector[i] - 1];

        while ( traversal_node ){

            tab[traversal_node->vertex1]++;
            traversal_node = traversal_node->next;
        
        }

    }
    for (int i = 0; i < 8; i++){

        printf("%d ", tab[i]);

    }
    printf("\n\n");

}   


// Ajuste la matrice selon les sommets supprimés [ Importante ]
void ajuster_matrice_faster(EDGE** matrice, int* sommets_cibles, int size ,int nbrelem, int* tableau_frequences, double* ft,double *conv, double *newPi){

    EDGE* traversal_node;
    EDGE* safe_node;
    EDGE* previous_edge;
    double frequence;
    int upper_bound = 0;
    int temp;

    //realloc avec le nouveau nb de sommets
    ft = realloc(ft,nbrelem* sizeof(double));

    //initialisation de ft à 1
    for(int i=0;i<nbrelem;i++){
       ft[i]=1;
    }


    for (int i = 0; i < nbrelem; i++){

        traversal_node = matrice[i];
        previous_edge = matrice[i];
        
        
        // Suppression des arcs sortants depuis les sommets supprimés.
        while ( traversal_node ){

            while ( isFound(traversal_node->vertex1, sommets_cibles, size) ){

                //printf("I get here with : %d\n", traversal_node->vertex1);
                // Si le sommet récupéré est le seul élément de la liste.
                if ( traversal_node->next == NULL && (traversal_node == matrice[i]) ){
                    
                    matrice[i] = NULL;
                    free(traversal_node);
                    traversal_node = NULL;
                    break;
            
                }

                // Si le sommet récupéré se situe à la fin de liste
                if ( traversal_node->next == NULL ){
                    
                    previous_edge->next = NULL;
                    free(traversal_node);
                    traversal_node = NULL;
                    break;

                }

                // Si le sommet se situe au début de la liste
                if ( traversal_node->next != NULL && (traversal_node == matrice[i]) ){

                    matrice[i] =  traversal_node->next;
                    free(traversal_node);

                }

                // Si le sommet se situe au milieu de la liste
                if ( traversal_node->next != NULL ){
                    
                    previous_edge->next = traversal_node->next;
                    traversal_node = traversal_node->next;
        
                }
            
            }

            // Treat non related
            if ( traversal_node ){
                

                frequence = tableau_frequences[traversal_node->vertex1];
                if ( frequence ){
                    
                    traversal_node->weight = 1 / ((1 / traversal_node->weight ) - frequence);

                }

                upper_bound = findBound(traversal_node->vertex1, sommets_cibles, size, 0, size - 1);
                temp = traversal_node->vertex1;
                traversal_node->vertex1 = traversal_node->vertex1 - upper_bound;
                
                //On met à 0 la case de ft correspondant au vertex1 car il a un degré sortant non nul
                ft[(traversal_node->vertex1) - 1] = 0;
                
                //initialisation de pi avec anciens résulats
                newPi[(traversal_node->vertex1) - 1] = conv[temp-1];

            }

            if ( traversal_node ){
    
                previous_edge = traversal_node;
                traversal_node = traversal_node->next;

            }

        }


    }


}