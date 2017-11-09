#include <stdlib.h>
#include "connect.h"

static int *id; //连通父节点
static int *sz; //连通树规模.
void connect_init(int N){
    int i;
    id = malloc(N*sizeof(int));
    sz = malloc(N*sizeof(int));
    for(i = 0; i < N; i++){
        id[i] = i;
        sz[i] = 1;
    }
}

static int find_father(int x){
    while(id[x] != x){
        x = id[x];
    }
    return x;
}

//index 1 2 3 4 5
//id    2 4             id[id[1]] -- 4;
//压缩后
//index 1 2 3 4 5
//id    4 4             id[1] -- 4;

static int find_father_and_compress_path(int x){
    //父节点不是自己.
    while(id[x] != x){
        //将父父节点index 交给自己 压缩路径.
        id[x] = id[id[x]];
        x = id[x];
    }
    return x;
}

int connect_find(int p, int q){
    return (find_father(p) == find_father(q));
}

void connect_union(int p, int q){
    int f1 = find_father(p);
    int f2 = find_father(q);
    if(f1 == f2)
        return ;

    if(sz[f1] > sz[f2]){
        //f1 做新的连通根节点
        id[f2] = f1;
        //f1 树 规模增大
        sz[f1] += sz[f2];
    }else{
        id[f1] = f2;
        sz[f2] += sz[f1];
    }
}

