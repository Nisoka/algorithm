#ifndef SYMBOL_H
#define SYMBOL_H

#include "../common/item_key.h"
/*
Symbol table 符号表.
 数据结构 实现的就是增删改查 四项基本操作. 如何让这四个操作更高效的实现就是数据结构的目的.
 不同的数据结构, 具有不同的性能特点, 也实现不同的增删改查操作.
 优先队列、堆、符号表他们的增删改查都各有特点,  所以需要使用不同的方式实现,
 因为不同的需要, 需要高效实现需要的操作, 所以如何组织数据就是最重要的事情.
 按不同的数据结构 组织 数据, 就能够形成 高效实现的操作 满足软件的需求.
 eg 需要快速排序(数组、链表)、需要快速查询(有序表)、需要快速合并(链表)
    快速定位删除等等不同的问题 需要不同的实现.
*/

void STinit(int );
int  STcount();
void STinsert(Item );
Item STsearch(Key );
void STdelete(Item );
Item STselect(int );
void STsort(void (*visit)(Item));

#endif // SYMBOL_H
