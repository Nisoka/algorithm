#ifndef HEAP_INDEX_H
#define HEAP_INDEX_H

#include <stdlib.h>
#include <stdio.h>

/*
  用于确定数据优先级的函数，我在这里将实现留给索引堆的用户，
  这样可以保证最大程度的灵活性，即对于任何数据，索引堆不关心数据本身，只关心数据之间的优先级,这里的i和j是数据数组（data）的下标，也就是pq中要存放的索引.
*/
int  Priority(int i, int j);

void PQinit(int n);
void PQinsert(int i);
int  PQdelmax();
void PQchange(int i);
int  PQempty();

#endif // HEAP_INDEX_H
