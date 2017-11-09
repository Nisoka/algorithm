#ifndef SORT_H
#define SORT_H

#include "../common/item_int.h"

//选择排序
void select_sort(Item a[], int l, int r);

void bubble_sort(Item a[], int l, int r);
void bubble_sort_pro(Item a[], int l, int r);

//插入排序
void insert_sort(Item a[], int l, int r);
void insert_sort_pro(Item a[], int l, int r);
void insert_sort_sentinel(Item a[], int l, int r);

void shell_sort(Item a[], int l, int r);

#endif // SORT_H
