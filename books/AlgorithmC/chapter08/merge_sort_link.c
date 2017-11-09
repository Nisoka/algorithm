#include "merge_sort_link.h"


link merge_link(link a, link b)
{
    struct node head;
    link c = &head;
    while( a!=NULL && b!=NULL){
        if(less(a->item, b->item)){
            c->next = a;
            c = a;
            a = a->next;
        }else{
            c->next = b;
            c = b;
            b = b->next;
        }
    }
    c->next = (a == NULL) ? b:a;
    return head.next;
}

link merge_sort_link(link c)
{
    link a, b;
    //这种情况下, 只剩下一个元素 或者 没有元素 说明元素已经有序 返回.
    if(c == NULL || c->next == NULL)
        return c;
    //如果有两个及以上元素 则需要排序.
    a = c;
    b = c->next;
    // 以b b->next 为判断结尾点, b 每次移动两个步长, c 移动一个步长
    // 最后c 就达到队列中间点.
    while( b!=NULL && b->next != NULL){
        c = c->next;
        b = b->next->next;
    }
    //这样b 就是link 的中间点.
    b = c->next;
    c->next = NULL;

    //自顶向下递归归并排序.
    return merge_link(merge_sort_link(a), merge_sort_link(b));
}


/*
 自底向上 的 归并排序
 1 通过一个循环链表(以链表为元素的链表), 来像数组的自底向上方式一样
 每次都是两两子文件归并为一个文件, 一直循环, 最后链表中只剩余一个元素 排序就完成了.
 2 通过使用 queue ADT 来实现, 实现起来复杂, 概念上还算简单.
 和上面的差不多 , 也就是将两个子文件出头队列,然后合并后在插入队列尾, 直到最终剩余一个元素, 就是已排序好的文件了
 这样的方式感觉好很多, 因为不需要计算算法的递归方程来实现循环, 直接通过ADT 的性质, 就能一直进行循环,并且根据性质就是
 自底向上的实现方式 --- 层序遍历树.
*/
void merge_sort_BU_queue(link t){
    link u;
    Queue q = queue_init(0);
    //每个元素拆分, 添加到queue中
    for(; t != NULL; t = u){
        u = t->next;
        t->next = NULL;
        queue_put(q, t);
    }

    t = queue_get(q);
    // 当queue为空, 说明没有需要被归并的link了
    // 不然每次都将上次归并好的t 向*末尾*加入queue, 然后*从头*取出两个进行归并.
    // 这样就是自底向上, 所有的1-1先归并形成2,然后放到后面等到全部1-1归并完后,进行2-2归并.
    while(!queue_empty(q)){
        queue_put(q, t);
        t = merge_link(queue_get(q), queue_get(q));
    }
    return t;
}
