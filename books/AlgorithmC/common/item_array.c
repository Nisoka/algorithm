#include "item_array.h"

void rand_init(Item a[], int N)
{
    int i;
    for(i = 0; i < N; i++){
        a[i] = item_rand();
    }
}

void scan_init(Item[], int *N)
{
    int i;
    for(i = 0; i < *N; i++){
        if(item_scan(&a[i]) == EOF)
            break;
    }
    *N = i;
}

void show(Item[], int start, int end)
{
    int i;
    for(i = start; i < end; i++){
        item_show(a[i]);
    }
    printf("\n");
}
