#include "priority_queue.h"

/*
//我们可以选择使用有序或无序序列 来作为链表或数组的实现.
//在保证数据项有序或者无序 之间做权衡,
//当希望插入需要常量时间时, 无序满足要求, 但是delmax就会需要遍历 如上.
// 无序序列是懒方法, 当需要时才做
//当希望delmax需要常量时间时, 有序满足要求, 但是insert就会需要遍历时间.
// 有序序列是良性方法, 提前处理以后需要的做的事.
// 任何时候都可以选择使用数组 或者 链表实现, 并作出基本权衡.
*/
static Item* pri_queue;
static int N;

/*
 9.1 基本操作实现 --
     无序(序列)数组 方式 实现优先队列
     使用无序序列实现, 当进行 delmax 时 需要更长时间
     但是insert 需要固定时间.
     与使用无序链表方式实现区别不大.
*/

#ifdef IMPLEMENT_USE_NOSORT_ARRAY


void pri_queue_init(int maxN){
    pri_queue = malloc(maxN*sizeof(Item));
    N = 0;
}

int pri_queue_empty(){
    return N == 0;
}

void pri_queue_insert(Item item){
    pri_queue[N++] = item;
}

Item pri_queue_delmax(){
    int i;
    int maxI = 0;
    for(i = 0; i < N; i++){
        if(less(pri_queue[maxI], pri_queue[i])){
            maxI = i;
        }
    }
    exch(pri_queue[maxI], pri_queue[N-1]);
    return pri_queue[--N];
}

#endif




#ifdef IMPLEMENT_USE_HEAP_ARRAY
/*
 9.2 堆数据结构
    高效支持优先队列的操作, 是优先队列的良好实现.
    堆数据结构 类似栈, 可以使用数组实现.
    对数据结构要求, 每个元素 关键字 要比其他两个指定位置的元素的关键字值要大.
    这样的描述 感觉就是树结构, 父节点和左右子节点. 所以堆是一种特殊的树.
    树满足父节点都大于所有子节点, 就说树是堆有序的.
        这个描述 正好是一个近似有序的数据结构, 所以用来实现优先队列 相当不错.
    堆是一个节点结合, 用数组表示, 关键字按照堆有序的完全二叉树排列.

    堆使用链表表示时, 就需要修改链表结构, 增加为三个连接, 来找寻节点.
    而使用数组实现, 则一个节点a[k] 他的子节点就是 a[2k] a[2k+1]
        对应的 a[k] 的父节点 就是a[k/2] 就是这么特殊的一个事实.
        eg a[3] 的父节点 a[3/2] -- a[1]
                用到了整数相除的特性.
注意 数组实现的堆,起始节点
    要是 a[1]. 这样两个子节点就是 a[2] a[3].
        a[2] 的两个子节点就是 a[4] a[5]
        a[3] 的两个子节点就是 a[6] a[7]
*/

/*
 9.3 基于堆的算法
 基于堆实现 优先队列
*/

/**
 * @brief fixUp 从k节点开始 向上堆化(满足堆结构的有序关系) 堆序数组a
 * @param a 堆序数组
 * @param k 从k节点开始
 */
void fixUp(Item a[], int k){
    //当未到达根节点时,与父节点比较(用到父节点, 所以结束条件 判断的不是1, 而是<1 根之前)
    //如果父节点较大, 说明还需要继续向上堆化. 直达根节点, 如此才形成堆有序
    while(k > 1 && less(a[k/2], a[k])){
        exch(a[k], a[k/2]);
        k = k/2;
    }
}

/**
 * @brief fixDown a 堆序数组 从k节点开始进行向下堆化
 * @param a 数组
 * @param k 堆化起点
 * @param N 节点总数(数组长度)
 */
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

void pri_queue_init(int maxN){
    pri_queue = malloc((maxN+1)*sizeof(Item));
    N = 0;
}

int pri_queue_empty(){
    return N==0;
}

//使用堆数据结构, 实际是类似树形结构, 插入操作的fixUp() 时间时 lgN.
//因为堆数据结构本身含有含有分治, 左右子节点-> 父节点. 所以每次都是 N/2 N/4 N/8 logN.
void pri_queue_insert(Item item){
    //插入新元素, N是当前最末尾元素 则插入位置为++N;
    pri_queue[++N] = item;
    //新插入了新元素, 要重新堆化. 插入位置是堆底, 所以fixUp();
    fixUp(pri_queue, N);
}

Item pri_queue_delmax(){
    exch(pri_queue[1], pri_queue[N]);
    fixDown(pri_queue, 1, N-1);
    return pri_queue[N];
}



#endif
