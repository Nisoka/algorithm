#include "queue.h"

#include "../common/link_base.h"

struct queue{
    link head;
    link tail;
};


link new_queue_node(Item item, link link_next){
    link t = new_link_node(item);
    t->item = item;
    t->next = link_next;
    return t;
}

Queue queue_init(int maxN){
    Queue q = malloc(sizeof(struct queue));
    q->head = NULL;
    q->tail = NULL;
    return q;
}

int queue_empty(Queue q){
    return q->head == NULL;
}

void queue_put(Queue q, Item item){
    if(queue_empty(q)){
        q->tail = new_queue_node(item, NULL);
        q->head = q->tail;
        return ;
    }

    q->tail->next = new_queue_node(item, NULL);
    q->tail = q->tail->next;
    return ;
}

Item queue_get(Queue q){
    Item item;
    link t;
    if(queue_empty(q))
        return item;

    item= q->head->item;
    t = q->head;
    q->head = q->head->next;
    free(t);
    return item;
}
