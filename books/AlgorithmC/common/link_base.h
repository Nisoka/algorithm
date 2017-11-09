#ifndef LINK_BASE_H
#define LINK_BASE_H

#include "common_use.h"
#include "item_int.h"

typedef struct node* link;

struct node{
    Item item;
    link next;
};

link new_link_node(Item item);
link link_malloc();
void link_free(link a);
void link_print(const link s);
link link_create(int length, int random);
#endif // LINK_BASE_H
