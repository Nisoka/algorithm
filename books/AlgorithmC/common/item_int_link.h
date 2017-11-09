#ifndef ITEM_LINK_H
#define ITEM_LINK_H

#include <stdlib.h>
#include <stdio.h>

typedef struct node* link;
struct node{
    int item;
    link next;
};

typedef link Item;

#define key(A) (A)
//less 判断是否<
#define less(A, B) (key(A->item) < key(B->item))
#define exch(A, B) {Item t = A; A = B; B = t;}
//less 则交换, 冒泡(小的)
#define compexch(A, B) if(less(B, A)) exch(A, B)

#endif // ITEM_LINK_H
