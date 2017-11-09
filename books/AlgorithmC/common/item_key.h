#ifndef ITEM_KEY_H
#define ITEM_KEY_H

#include <stdlib.h>
#include <stdio.h>

typedef int Key;
typedef struct {
    Key key;
    int value;
}Item;

#define key(A) (A)
//less 判断是否<
#define less(A, B) (key(A) < key(B))
#define exch(A, B) {Item t = A; A = B; B = t;}
//less 则交换, 冒泡(小的)
#define compexch(A, B) if(less(B, A)) exch(A, B)
#define min(A, B) (A < B) ? A : B

#endif // ITEM_KEY_H
