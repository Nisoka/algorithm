#include "stack.h"

//implement use array
//implement use link

/*
链表实现 和 数组实现的特点比较
链表实现
    1 在push pop时 需要构造 析构节点, 插入 删除 所以需要更多的时间
    2 空间上, 空间占用更合理.
    所以 如果实际问题 更多用于保存数据, 而较少的push pop操作可以选用链表
    或者 栈的大小变化比较大时, 因为空间利用合理 应该选用链表
数组实现
    1 push pop 方便实现 只需要用一个 cur 索引即可实现.
    2 空间上, 利用不合理, 要先分配固定空间, 所以可能会有空间浪费
    所以 如果实际问题 有很频繁的 push pop 使用数组实现 可以提高操作速度
    或者 数据很多常常满栈时, 使用数组也很合理.

*/

/* 实际问题 来选择 数组 链表实现抽象数据类型
// 数组 快速访问但是需要预测数据项最大数目
// 链表 空间利用合理但是访问速度下降

// 为特定问题 提供ADT 的核心就是 问题情况
//          进而选择合适的数据结构 和 实现操作.
*/

#ifdef IMPLEMENT_USE_ARRAY
static Item* s;
static int N;

void stack_init(int maxN){
    s = malloc(maxN*sizeof(Item));
    N = 0;
}

int stack_empty(){
    return N==0;
}

void stack_push(Item item){
    s[N++] = item;
}

Item stack_pop(){
    return s[--N];
}
#endif

#ifdef IMPLEMENT_USE_LINK
typedef struct node_stack* link_stack;
struct node_stack{
    Item item;
    link_stack next;
};
static link_stack head;

link_stack new_node_stack(Item item, link_stack next){
    link_stack t = malloc(sizeof(struct node_stack));
    t->item = item;
    t->next = next;
    return t;
}

void stack_init(int maxN){
    head = NULL;
}

int stack_empty(){
    return head==NULL;
}

void stack_push(Item item){
    head = new_node_stack(item, head);
}

Item stack_pop(){
    link_stack t = head;
    head = t->next;
    Item item = t->item;
    free(t);
    return item;
}

#endif

#ifdef IMPLEMENT_INDEX_NO_REPEAT
static Item *s;
static int  *t;  //s 栈的具体实现, t 保存对象是否存在的标志.
static int N;

void stack_init(int maxN){
    int i;
    s = malloc(maxN*sizeof(Item));
    t = malloc(maxN*sizeof(int));
    for(i = 0; i < maxN; i++)
        t[i] = 0;
    N = 0;
}

void stack_empty(){
    return N==0;
}

void stack_push(Item item){
    if(t[item] == 1)
        return ;

    s[N++] = item;
    t[item] = 1;
}

Item stack_pop(){
    --N;
    t[s[N]] = 0;
    return s[N];
}
#endif
