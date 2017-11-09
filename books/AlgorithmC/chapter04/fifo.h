#ifndef FIFO_H
#define FIFO_H
/*
p103 - p104
    抽象数据类型, 我们可以随意的进行细节实现,
只要我们暴露给客户的 客户能够知道的数据组织结构符合抽象数据类型描述的？？.
(例如栈 客户只知道栈是一个先入后出这样的数据结构, 而不知道具体细节,
或者说 因为抽象出了一个高层次的操作接口,而不需要知道具体实现, 而且具体实现可以随意修改以适应不同需求,
这样的抽象类型 就是抽象数据类型.)
*/

#define IMPLEMENT_FIFO_USE_LINK
#define IMPLEMENT_FIFO_USE_ARRAY

#include "item.h"
//书中是用 queue.
void fifo_init(int);
int  fifo_empty();
void fifo_put(Item);
Item fifo_get();

#endif // FIFO_H
