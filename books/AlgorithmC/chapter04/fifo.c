#include "fifo.h"

#ifdef IMPLEMENT_FIFO_USE_LINK

#include "../common/link_base.h"
link head, tail;
link new_fifo_node(Item item, link next){
    link x = new_link_node(item);
    x->item = item;
    x->next = next;
    return x;
}

void fifo_init(int maxN){
    head = NULL;
    tail = NULL;
}

int fifo_empty(){
    return head == NULL;
}

void fifo_put(Item item){
    if(head == NULL){
        tail = new_fifo_node(item, tail);
        head = tail;
        return ;
    }
    tail->next = new_fifo_node(item, tail->next);
    tail = tail->next;
}

Item fifo_get(){
#ifdef MY_IMPLEMENT
    link_fifo x = head;
    //保存数据.
    head = head->next;
    //获得Item
    Item t = x->item;
    //释放无用节点
    free(x);
    return t;
#else
    Item item = head->item;
    link t = head->next;
    head = head->next;
    free(t);
    return item;
#endif
}

#ifdef IMPLEMENT_FIFO_USE_ARRAY
// 使用数组实现 fifo , 数组不应该频繁的进行插入删除(插入删除 会有很大的操作)
// 那么fifo 可以是通过 head tail 游标方式 实现.
// 那么又 如果逐渐增大数组大小, 同时前面逐渐获得数据, 那么前面的数组位置都浪费了.
// 固定数组大小, 循环使用 数组, head tail 通过 index%N 的方式 形成类似循环实现 提高空间效率.

static Item *q;
static int N;
static int head, tail;

void fifo_init(int max){
    q = malloc((max+1)* sizeof(Item));
    N = max+1;
    head = 0;
    tail = 0;
}

int fifo_empty(){
    return head%N == tail;
}

void fifo_put(Item item){
    tail = tail%N;
    q[tail++] = item;
}

Item fifo_get(){
    head = head%N;
    return q[head++];
}

// 下堆栈 和 fifo 队列都是 一个 更通用的ADT的实例 -- 广义队列.
// 不过 下堆栈和 fifo 的区别是删除元素时 使用的规则不同. 而规则不同那么就会选择不同的广义队列实现
// 下堆栈 or fifo.
// 广义队列中最重要的一个实例是 符号表 ADT
//  每个项都有键这个属性, 删除操作是 删除那些键 与 给定键相同的数据项。 会讨论数十种实现.
// 其他的还有 优先队列 随机队列 双向队列 等等.
#endif
