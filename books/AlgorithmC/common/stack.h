#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>

//#define CHAR_ITEM
//#define IMPLEMENT_USE_ARRAY
#define IMPLEMENT_USE_LINK
//#define IMPLEMENT_INDEX_NO_REPEAT

#ifdef IMPLEMENT_USE_LINK
#define INT_ITEM
#endif

#ifdef CHAR_ITEM
#include "item_char.h"
#else
#include "item_int.h"
#endif


void stack_init(int);
int  stack_empty();
void stack_push(Item);
Item stack_pop();

/*
//计算机程序就是按照栈方式工作的, 频繁推迟任务, 然后弹出任务.
// 因此栈 是很多算法 最基本的数据结构
//强迫实现ADT定义的操作规则 就表示了ADT抽象数据类型.而具体实现可以任意.

ADT 接口的作用:
    1 抽象数据类型的接口方式的抽象描述
    2 客户和实现之间的锲约.
*/
#endif // STACK_H
