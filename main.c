#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrice.h"



int main()
{
   int nbrSommet , i, sommet1,sommet2, arc;
   long nbrArc;
   double poid;
   char chaine[1000000]="";
   FILE* fichier = NULL;

   double *pi;
   double *res;

   char * pch1;

   sommet1 = 0;
   sommet2 = 0;
   poid = 0;
   arc = 0;

   fichier = fopen("wb-edu.txt","r+");

   if(fichier != NULL)
   {
       fgets(chaine, 1000000, fichier); //prendre le premier element de notre fichier (matrice) c'est le nombre de sommets
       nbrSommet =atoi(chaine); // convertire le char en int en utilisant la fonction atoi

       fgets(chaine,1000000, fichier); // lire la deuxieme ligne (nombre d'arc)
       nbrArc =atol(chaine); // convertire le char en long

       printf("le nombre de sommet : %d \n",nbrSommet);
       printf("le nombre d'arc : %ld \n",nbrArc);




       EDGE** T = malloc(sizeof(EDGE*)* nbrSommet);// creer notre tableau de EDGE*



        for(i = 0;i<nbrSommet;i++){
            T[i]=initialisation();
        }




        while (fgets(chaine, sizeof(chaine), fichier) != NULL) // On lit le fichier a partire de la 3 iem ligne tant qu'on ne reçoit pas d'erreur (NULL)
        {
            // On cherche à récupérer, un à un, tous les mots  de la ligne i
            // et on commence par le premier.

            pch1 = strtok (chaine," ");
            sommet1 = atoi(pch1);// sommet i

            pch1 =strtok (NULL," ");
            arc = atoi(pch1);//nbr arc du sommet i


             //printf("le sommet : %d a %d successeur \n",sommet1,arc);
               while (pch1 != NULL )
                {

                 // On demande le j iem successeur.
                   pch1 =strtok (NULL," ");

                   if(pch1 != NULL)
                   {
                       sommet2 = atoi(pch1);

                   }

                   // On demande le poids de l'arc vers j iem successeur.
                   pch1 =strtok (NULL," ");

                   if(pch1 != NULL)
                   {

                       poid = atof(pch1);

                       T[sommet2-1] = insertion(T[sommet2-1],sommet1,poid);
                   }


                }

        }
        fclose(fichier);


       /* for(i = 0 ; i<nbrSommet;i++)
            {

                afficherListe(T[i],i+1);


            }*/

        pi = calloc(nbrSommet, sizeof(double));
        initvect(pi,nbrSommet);


        double *v1 = calloc(nbrSommet, sizeof(double));

         /*multiplication(T,nbrSommet,pi,v1);
         affichervect(nbrSommet,v1);*/



       /* multiplication(T,nbrSommet,pi,v1);
        pi = v1;
        v1 = calloc(nbrSommet, sizeof(double));
         multiplication(T,nbrSommet,pi,v1);
        pi = v1;
        v1 = calloc(nbrSommet, sizeof(double));
         multiplication(T,nbrSommet,pi,v1);
        pi = v1;
        v1 = calloc(nbrSommet, sizeof(double));
         multiplication(T,nbrSommet,pi,v1);
        pi = v1;
        v1 = calloc(nbrSommet, sizeof(double));
         multiplication(T,nbrSommet,pi,v1);
         affichervect(nbrSommet,v1);*/


        /* for(int i = 0 ;i<173 ; i++){
            multiplication(T,nbrSommet,pi,v1);
            pi = v1;
            v1 = calloc(nbrSommet, sizeof(double));

         }*/


       /* printf("convergence \n");
        double  *conv =calloc(nbrSommet, sizeof(double));
        conv = convergence(T,nbrSommet,pi,v1);

        affichervect(conv);*/

        //multiplication(T,nbrSommet,pi,v1);

        double  *conv =calloc(nbrSommet, sizeof(double));
        conv = convergence(T,nbrSommet,pi,v1);









   }
   else
   {
    printf("impossible de lire le fichier !");
   }

}
