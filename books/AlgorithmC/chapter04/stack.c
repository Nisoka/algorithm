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

void stack_init(int max){
    s = malloc(max*sizeof(Item));
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
#include "../common/link_base.h"
link head;
link new_stack_node(Item item, link next){
    link t = new_link_node(item);
    t->next = next;
    return t;
}

void stack_init(int max){
    head = NULL;
}

int stack_empty(){
    return head == NULL;
}

void stack_push(Item item){
    head = new_stack_node(item, head);
}

Item stack_pop(){
    link t = head;
    Item item = t->item;
    head = head->next;
    free(t);
    return item;
}

#endif

#ifdef IMPLEMENT_INDEX_NO_REPEAT
//实际这个no_repeat 无重复要求实际上是要求需要搜索查找功能.
// 使用hash表exist_flag, 来表示是否存在, Item需要通过hash函数获得hashkey, 然后直接进行访问.
// 一般的hash函数 都是使用取模hash函数.
static int *exist_flag;
static Item *s;
static int N;
static int max_N;

//要保证max_N 大于两倍 内容 或者使用动态表
//这个hash函数方式 不对, 不应该这么写.具体看 散列表一章.
int hash_key(Item item){
    int key = *(int *)&(item);
    key = key%max_N;

    return key;

    if(exist_flag[key] == 1){
        //开发式表
    }
}

void stack_init(int max){
    int i;
    s = malloc(max * sizeof(Item));
    exist_flag = malloc(max * sizeof(int));

    for(i = 0; i < max; i++)
        exist_flag[i] = 0;
    N = 0;
    max_N = max;
}

int stack_empty(){
    return N == 0;
}

void stack_push(Item item){
    if(exist_flag[hash_key(item)] == 1)
        return ;
    s[N++] = item;
    exist_flag[hash_key(item)] = 1;
}

Item stack_pop(){
    Item item = s[--N];
    exist_flag[hash_key(item)] = 0;
    return item;
}
#endif
