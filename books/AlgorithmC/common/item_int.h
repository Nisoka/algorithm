#ifndef ITEM_H
#define ITEM_H

#include <stdlib.h>
#include <stdio.h>

typedef int Item;

#define key(A) (A)
#define eq(a, b) (a == b)
#define min(A, B) (A < B) ? A : B
//less 判断是否<
#define less(A, B) (key(A) < key(B))
#define exch(A, B) {Item t = A; A = B; B = t;}
//less 则交换, 冒泡(小的)
#define compexch(A, B) if(less(B, A)) exch(A, B)

#define print_item(item) printf("%d ", item)

Item item_rand();
int  item_scan(Item *v);
void item_show(Item v);

#endif // ITEM_H
