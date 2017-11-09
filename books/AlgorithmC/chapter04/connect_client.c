#include <stdio.h>
#include <stdlib.h>
#include "connect.h"

int main(int argc, char *argv[]){
    int p, q, N = atoi(argv[1]);
    connect_init(N);
    while(scanf("%d %d", &p, &q) ==2){
        if(!connect_find(p, q)){
            connect_union(p, q);
            printf("%d %d\n", p, q);
        }
    }
}


