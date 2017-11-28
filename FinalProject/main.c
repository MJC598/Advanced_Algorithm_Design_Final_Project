#include <stdio.h>
#include <stdlib.h>
#include "vector.h"



int main(int argc, char** argv) {

    struct vector maze;
    init_vector(&maze);
    int i, j;
    for(i = 0; i < 10; i++){
        for(j = 0; j < 10; j++){
            insert_element_vector(&maze, 'x', i, j);
        }
    }
    
    for(i = 0; i < 10; i++){
        for(j = 0; j < 10; j++){
            printf("%c ", access_element_vector(&maze, i, j));
        }
        printf("\n");
    }
    
    free_vector(&maze);

    return (EXIT_SUCCESS);
}

