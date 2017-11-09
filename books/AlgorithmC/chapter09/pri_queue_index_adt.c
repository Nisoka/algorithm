#include "pri_queue_index_adt.h"

/*
 这个实现方式 在实际中非常有用.
*/

#define maxPQ 1000

typedef int Item;
static int N;

//索引数组 - pq
Item pq[maxPQ+1];

//逆序索引数组, 用来索引pq的? 将数组索引作为句柄处理.???
//看来还是要去看看 6章索引指针排序那块. 不明白作用是什么
//索引数组句柄数组 - qp;
int qp[maxPQ+1];

//data

int less(int i, int j)
{
    return (data[pq[i]] < data[pq[j]]);
}
//开始  i = 3, j = 6;
//      pq[i] = 3  pq[j] = 6;
//      data[3] = 5,  data[6] = 11;
//那么 就是 data[pq[3]] < data[pq[6]]. 需要的是 data[pq[3]] > data[pa[6]]
//需要交换exch, 交换的是 pq[3] pq[6]的内容. 得到data[pq[3]] = data[6]
// data 不变, 那么就是 pq[i] pq[j] 保存的index即可.
void exch(int i, int j){
    int t;
    //主要工作
    //为什么交换的是qp 的两个元素呢？
    t = qp[i];
    qp[i] = qp[j];
    qp[j] = t;

    //qp
    pq[qp[i]] = i;
    pq[qp[j]] = j;
}

void fixUp(Item a[], int k){
    //当未到达根节点时,与父节点比较(用到父节点, 所以结束条件 判断的不是1, 而是<1 根之前)
    //如果父节点较大, 说明还需要继续向上堆化. 直达根节点, 如此才形成堆有序
    while(k > 1 && less(a[k/2], a[k])){
        exch(a[k], a[k/2]);
        k = k/2;
    }
}

//N 是节点数, 不是数组长度
//从k节点 向下堆化, N 节点数.
void fixDown(Item a[], int k, int N){
    int i;
    //当k未达到堆底. k 还有子节点(2k 2k+1)
    while(2*k <= N){
        i = 2*k;
        /*
        判断两个子节点那个比较大. 堆化需要较大的向上, 较小的留下, 不然还不能堆有序.
        i < N; 2k<N, 说明有两个子节点,
        有特殊情况 是2k == N;(N - 14个节点, k 为 7 时, k 此时只有一个子节点.
        所以i+1 就发生越界了, 所以必须要判断i < N 时候才进行两个子节点判断
        */
        if(i < N && less(a[i], a[i+1]))
            i++;
        if(!less(a[k], a[i]))
            break;
        //k -> 2k 向下堆化.
        exch(a[k], a[i]);
        k = i;
    }
}




void pq_init(){
    N = 0;
}

int pq_empty(){
    return N==0;
}

void pq_insert(int k){
    qp[k] = ++ N;
    pq[N] = k;
    fixUp(pq, N);
}


int pq_delmax()
{
    exch(pq[1], pq[N]);
    fixDown(pq, 1, --N);
    return pq[N+1];
}

void pq_change(int k)
{
    fixUp(pq, qp[k]);
    fixDown(pq, qp[k], N);
}

void pq_delete(int)
{

}
