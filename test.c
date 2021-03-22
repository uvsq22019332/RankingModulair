#include <stdlib.h>
#include <stdio.h>




int main(int argc, char* agrv){

    int* ptr = malloc(1 * sizeof(int));
    *ptr = 5;
    printf("%p\n", ptr);
    free(ptr);
    ptr = NULL;
    printf("%p\n", ptr);


    return 0;
}