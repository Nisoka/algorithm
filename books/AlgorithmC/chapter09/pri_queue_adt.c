#include "pri_queue_adt.h"



struct pq_node{
    Item key;
    pq_link prev;
    pq_link next;
};

struct pri_queue{
    pq_link head;
    pq_link tail;
};

Pri_Queue pri_queue_init()
{
    Pri_Queue pq = malloc(sizeof(struct pri_queue));
    pq_link h = malloc(sizeof(struct pq_node));
    pq_link t = malloc(sizeof(struct pq_node));
    h->prev = t;
    h->next = t;
    t->prev = h;
    t->next = h;
    pq->head = h;
    pq->tail = t;
    return pq;
}

int pri_queue_empty(Pri_Queue pq){
    return pq->head->next->next == pq->head;
}

pq_link pri_queue_insert(Pri_Queue pq, Item item)
{
    pq_link t = malloc(sizeof *t);
    t->key = item;
    //插入为第一个元素, 在head 之后. 指向原第一个元素
    t->next = pq->head->next;
    //原本第一个元素pre指向现在第一t.
    t->next->prev = t;
    //t pre指向head.
    t->prev = pq->head;
    //pd->head->next 指向现在第一个元素t.
    pq->head->next = t;

    return t;
}

Item pri_queue_delmax(Pri_Queue pq)
{
    Item max;
    struct pq_node* t;
    struct pq_node* x = pq->head->next;//第一个元素
    //遍历max, 迭代切换x为key max
    for(t = x; t->next!= pq->head; t = t->next)
        if(t->key > x->key)
            x = t;
    max = x->key;

    //删除x,
    //1 x的下一个元素的prev 指向原本x->prev.
    //2 x的上一个元素的next 指向原本x->next;
    x->next->prev = x->prev;
    x->prev->next = x->next;
    free(x);
    return x;
}

void pri_queue_change(Pri_Queue pq, pq_link x, Item item)
{
    x->key = item;
}

void pri_queue_delete(Pri_Queue pq, pq_link x)
{
    x->next->prev = x->prev;
    x->prev->next = x->next;
    free(x);
}

void pri_queue_join(Pri_Queue a, Pri_Queue b)
{
    //衔接 a 尾部 与 b 头部
    a->tail->prev->next = b->head->next;
    b->head->next->prev = a->tail->prev;

    a->head->prev = b->tail;
    b->tail->next = a->head;
    free(a->tail);
    free(b->head);

}
