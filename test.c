#include <stdio.h>
#include <stdlib.h>
#include "operation.h"

int main(){


    int tab[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int tab2[2] = {6,2};
    int counter = 1;

    for (int i = 0; i < 10; i++){

        if ( isFound(tab[i], tab2, 3)){

            tab[i] = tab[i + 1];
            i++;

            while ( !isFound(tab[i], tab2, 2) && (i < 8) ){

                tab[i] = tab[i + counter];
                i++;
            }
            counter++;

        }
        
    }

    for (int i = 0; i < 10; i++ ){

        printf("%d ", tab[i]);

    }
    printf("\n \n");

}