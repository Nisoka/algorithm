#include "queue.h"

typedef struct node_queue* link_queue;

struct node_queue{
    Item item;
    link_queue next;
};

struct queue{
    link_queue head;
    link_queue tail;
};


link_queue new_queue_link(Item item, link_queue link_next){
    link_queue t = malloc(sizeof(struct node_queue));
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
        q->tail = new_queue_link(item, NULL);
        q->head = q->tail;
        return ;
    }

    q->tail->next = new_queue_link(item, NULL);
    q->tail = q->tail->next;
    return ;
}

Item queue_get(Queue q){
    Item item;
    link_queue t;
    if(queue_empty(q))
        return item;

    item= q->head->item;
    t = q->head;
    q->head = q->head->next;
    free(t);
    return item;
}


