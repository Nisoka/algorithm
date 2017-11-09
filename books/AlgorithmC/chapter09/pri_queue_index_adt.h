#ifndef PRI_QUEUE_INDEX_ADT_H
#define PRI_QUEUE_INDEX_ADT_H

/*
// 使用 索引 来间接引用操作数组, 实现堆数据结构.
// 使用数组下标索引 作为句柄来实现优先队列. 通过数组下标作为句柄 可以实现优先队列的所有操作.
// 这个优先队列的实现 并不使用数据项数组自身, 而是使用数据项数组索引作为数据结构.
// 不是维持自身 而是维持数组索引.
// 这部分写的是傻逼, 不看这一小节了 9.6
*/
int less(int i, int j);
void pq_init();
int pq_empty();
void pq_insert(int);
int pq_delmax();
void pq_change(int);
void pq_delete(int);

#endif // PRI_QUEUE_INDEX_ADT_H
