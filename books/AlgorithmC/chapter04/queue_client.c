#include <stdlib.h>
#include "queue.h"

#define M 10

int main(int argc, char *argv[]){
    int i, N;
    N = atoi(argv[1]);
    Queue queues[M];
    for(i = 0; i < M; i++){
        queues[i] = queue_init(N);
    }
    for(i = 0; i < N; i++)
        queue_put(queues[rand()%M], rand()%100);

    for(i = 0; i < M; i++, printf("\n")){
        while(!queue_empty(queues[i])){
            printf("%d ", queue_get(queues[i]));
        }
    }
    return 0;
}
