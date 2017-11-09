#ifndef PRI_QUEUE_ADT_H
#define PRI_QUEUE_ADT_H

#include "../common/item_int.h"


/*
 9.5 无序双向链表实现 优先队列一级ADT
*/

typedef struct pri_queue* Pri_Queue;
typedef struct pq_node* pq_link;

Pri_Queue pri_queue_init();
int pri_queue_empty(Pri_Queue pq);
pq_link pri_queue_insert(Pri_Queue pq, Item item);
Item pri_queue_delmax(Pri_Queue pq);
void pri_queue_change(Pri_Queue pq, pq_link x, Item item);
void pri_queue_delete(Pri_Queue pq, pq_link x);
void pri_queue_join(Pri_Queue a, Pri_Queue b);


#endif // PRI_QUEUE_ADT_H
