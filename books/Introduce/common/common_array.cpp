#include "common_array.h"


void generate_dim_square_int(int **a, int dim){
    a = (int**)malloc(dim * sizeof(int*));
    for(int i = 0; i < dim; i++)
        a[i] = (int*)malloc(dim * sizeof(int));

    for(int i = 0; i < dim; i++)
        for(int j = 0; j< dim; j++)
            a[i][j] = 0;
}

common_array::common_array()
{

}
