#ifndef ITEM_ADT_H
#define ITEM_ADT_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct record{
    char name[30];
    int num;
};

typedef struct record* Item;

//#define RECORD_SORT_KEY_NUM
//#define RECORD_SORT_KEY_NAME
#define RECORD_SORT_MULTI_KEY

int less(Item a, Item b);
#define exch(A, B) {Item t = A; A = B; B = t;}
Item item_rand();
int  item_scan(Item *v);
void item_show(Item v);
#endif // ITEM_ADT_H
