#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "../common/item_int.h"


//#define IMPLEMENT_USE_NOSORT_ARRAY
#define IMPLEMENT_USE_HEAP_ARRAY
/*
基本优先队列ADT 是一种数据结构, 数据项中带有关键字, 支持两种基本操作
// 向有点队列插入新的数据项, 删除优先队列中关键字最大的数据项.
//优先队列有很多应用场景
// 1 排序 2 模拟系统 3 作业调度
//这些函数的实现 使用数组或者链表

不同的实现方式 对于不同的操作有不同的性能特征, 所以不同的应用问题会需要特定的高效操作, 应该选用不同的实现方式.
 两个重要的基本权衡, 链表内存分配 or 顺序内存分配.
 应用程序使用的软件包的问题.
 更高级的算法 会使用 优先队列的客户端作为数据结构.

 所以不同的优先队列的实现方式就是重中之重, 不同的实现方式 会得到不同的性能特征.!
*/
void pri_queue_init(int );
int  pri_queue_empty();
void pri_queue_insert(Item );
Item pri_queue_delmax();

void fixUp(Item a[], int k);
void fixDown(Item a[], int k, int N);



#endif // PRIORITY_QUEUE_H
