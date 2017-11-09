#include "priority_queue.h"

//使用优先队列 排序
void pri_queue_sort(Item a[], int l, int r){
    int k;
    pri_queue_init(10000);
    for(k =  l; k <= r; k++)
        pri_queue_insert(a[k]);
    for(k = r; k >= l; k--)
        a[k] = pri_queue_delmax();
}


/*
 9.4 堆排序
 利用优先队列排序, 就会利用优先队列的额外空间。
 实际上 堆数据结构直接实现 堆排序, 更加方便.
 */
void heap_sort(Item a[], int l, int r){
    int k, N= r-l+1;
    //pri_queue 从a+l-1开始的数组构建堆有序关系.
    Item *pri_queue = a+l-1;
    //从N/2逐个进行子树 堆化.
    //这样pri_queue 指向的数组就是优先队列
    for(k = N/2; k >= l; K--)
        fixDown(pri_queue, k, N);
    //
    while(N>1){
        exch(pri_queue[1], pri_queue[N]);
        fixDown(pri_queue, 1, --N);
    }

}
