#include <stdlib.h>
#include "link_node_interface.h"

// **    数组名 既能用于数组索引访问数据, 又能作为指针访问数据.
// 对应的 指针   不仅能作为指针访问数据, 也能作为数组索引访问数据.
// 数组名 被实现为指针, 指针可以通过 +n 来快速访问任意位置数据.

//typedef struct node* link;
// link 是 node指针, 所以可以用来指代 node数组. 并可以使用索引访问.
link freelist;
void initNodes(int N){
    int i = 0;
    //malloc 申请空间, 得到地址. 使用node* 保存, freelist可以表示数组.
    freelist = malloc((N+1)*sizeof(struct node));
    for(i = 0; i < N+1; i++){
        //link 是node指针,
        freelist[i].next = &freelist[i+1];
    }
    freelist[N].next = NULL;
}

void insertNode(link list, link x){
    //被插入的链表需要 保存next, 因为插入后 指向了新的node - x.
    x->next = list->next;
    list->next = x;
}

link deleteNode(link list){
    link t = list->next;
    list->next = t->next;
    return t;
}

link newNode(int i){
    link x = deleteNode(freelist);
    x->item = i;
    x->next = x;
    return x;
}

void freeNode(link x){
    insertNode(freelist, x);
}

link Next(link x){
    return x->next;
}

int Item(link x){
    return x->item;
}
