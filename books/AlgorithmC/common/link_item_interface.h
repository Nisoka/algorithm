#include <stdlib.h>
#include <stdio.h>

#include "item_int.h"

typedef struct node* link;

struct node{
  Item item;
  link next;
};

link new_link(Item item, link next);
link init(int);
void show(link v);
link sort();
