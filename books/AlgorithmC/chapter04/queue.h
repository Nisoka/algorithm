#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include "item.h"

typedef struct queue* Queue;

void queue_dump(Queue q);
Queue queue_init(int maxN);
int queue_empty(Queue q);
void queue_put(Queue q, Item item);
Item queue_get(Queue q);


#endif // QUEUE_H
