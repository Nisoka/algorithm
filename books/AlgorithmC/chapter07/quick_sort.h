#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "../common/item_int.h"
#include "../common/stack.h"

#define eq(A, B) (!less(A, B) && !less(B, A))
#define push2(A, B) stack_push(B); stack_push(A)

int  partition(Item a[], int l, int r);
void quick_sort(Item a[], int l, int r);

void quick_sort_stack(Item a[], int l, int r);
void quick_sort_pro(Item a[], int l, int r);
#endif // QUICK_SORT_H
