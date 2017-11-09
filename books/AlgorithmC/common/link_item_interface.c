#include "link_item_interface.h"

link new_link(Item item, link next){
  link x = malloc(sizeof(struct node));
  x->item = item;
  x->next = next;
  return x;
}
link init(int){
  return NULL;
}

void show(link v){
  printf("%d ", v->item);
}

link link_select_sort(link h){
  link max;
  link t;
  link out;
  while(h->next != NULL){
    max = findmax(h);
    t = max->next;
    max->next = t->next;
    t->next = out;
    out = t;
  }
  return out;
}

link sort(link h){
  return link_select_sort(h);
}
