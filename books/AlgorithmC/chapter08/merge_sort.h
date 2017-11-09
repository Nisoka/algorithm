#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "../common/item_int.h"
#include "../common/sort.h"

//归并操作
void merge_ab(Item c[], Item a[], int N, Item b[], int M);
//归并排序
void merge_sort(Item a[], int l, int r);
//归并排序的改进算法pro. 1 小文件使用插入排序 2 不复制数组
void merge_sort_AB(Item a[], int l, int r);
//自底向上的 非递归排序 先了解问题规模递归方程.
void merge_sort_BU(Item a[], int l, int r);
#endif // MERGE_SORT_H
