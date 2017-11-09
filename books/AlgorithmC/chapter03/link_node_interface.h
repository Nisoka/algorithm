#ifndef LINK_NODE_INTERFACE_H
#define LINK_NODE_INTERFACE_H

typedef int itemType;
typedef struct node* link;
struct node{itemType item; link next;};
typedef link Node;

void initNodes(int N);
link newNode(int i);
void freeNode(link x);
void insertNode(link list, link x);
link deleteNode(link list);
link Next(link x);
int Item(link x);
#endif // LINK_NODE_INTERFACE_H
