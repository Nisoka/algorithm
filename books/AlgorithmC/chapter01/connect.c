#include <stdio.h>
#include "connect.h"

#define N 1000
/*
 核心是将问题用已知数据结构描述表示
 例如连通问题, 到底怎么描述连通怎么表示连接?
表示连接是不可行的(链表?) 那么已知数据结构 数组 链表队列等等就进入你的考虑范围了
表示连接 可以用保存记录方式 表示 (空间能够表示一切).
*/
/*
//connect 问题 怎么表示两个点是否连通?
//      用集合表示的, 如果点使连通的,那么他们都在一个集合中.
// 那么怎么表示集合的呢?
//      1 用数组标记表示集合, 如果两个点对应的标记数组的标记值一样说明在同一个集合.
//      2 利用树 数据结构表示, 树的实现使用数组基本数据结构实现的点对应的索引数组, 索引父连通节点.

//抽象出 基本抽象操作 设计算法和数据结构来实现基本抽象操作.
// 1 能够更加明确问题的解决方法. 将大问题 变为小问题
// 2 能够移植使用到其他类似问题上.

// ---> 设计算法的一般步骤是
// 1 明确问题 抽象出基本抽象操作
// 2 设计数据结构 来 使抽象操作易于实现 或者在这步中 应该是设计让抽象操作更容易描述的数据结构.
//      例如在连通问题中 怎么表示两个点在同一个集合是核心问题(也就是基本抽象操作)
        也就是说找到一个数据结构来 清晰的表示两个点是否在一个集合(连通)
        当使用考虑到用代表 表示集合时 就更让你的数据结构更进一步了
// 3 根据数据结构来设计抽象操作.
//      当数据结构描述 核心问题特别清晰的时候, 也就是基本抽象操作易于描述 易于计算.
        那么什么问题 用什么样的数据结构更容易表示表达容易设计算法, 就是本书通过一些实例教你的.
        什么样的问题 能够抽象为什么样的数据结构, 这种抽象问题的思维方式 是最高级核心原理.
eg
在连通问题中, 数据结构就是 用于表示和处理 抽象结合.
        在本问题中 最重要的就是 高效支持 查找和合并操作的数据结构.
*/
/* 
   连通问题 - 快速查找算法
   数据结构: 直接使用线性表 - 数组.
       index 代表某个 对象
       id[index] 代表对象连通标记, 值 代表连通到的目标对象idnex.
            连通标记相同代表 对象连通.
       特点-主要利用点:
          主要是因为索引直接代表对象, contant内容表示连通性, 这时候随机访问直接就相当于直接访问对象的连通性。
          而连通性 使用连通道的目标对象(index)表示 更是一个好的trick
   算法: 
       查找: 判断两个 id[index] 是否相等
       合并: 当两个对象不连通, 需要合并, 则直接将前一个对象p 以及所有与前一个对象p连通的对象, 都标记为id[q] 即都与q连通.
   性质:
       求解N个对象的连通问题, 如果执行M次合并操作, 快速查找算法至少执行M*N条指令.
   优点:
       查找比较快速, 直接对象索引, 标记判断即可知道是否连通.
   缺点:
       合并效率低, 合并两个对象, 要遍历所有对象,将p连通对象都连通到q。
       遍历的执行次数是N。

      
 */
void connect_quick_find(){
  //id[N] N 个数据点, 原本全部连通.
  // index 是每个数据
  // id[index] 是标记, 两个数据index1 index2 如果连通, 那么id[index1] == id[index2] 
  int i, j, p, q, t, id[N];
  for (i = 0; i< N; i++)
    id[i] = i;
  
  // 每个输入对 判断是否连通.
  while(scanf("%d %d", &p, &q)== 2){
    //1 查找: 直接查找 是否连通.
    if(id[p] == id[q])
      continue;

    //2 不连通合并 如果不连通, 则连通两者, 因为p 可能连通着别的数据, 直接搜索所有连接者,一起连接.
    // 这样每次连接 都会将连接者的连通标记 都标记为 q的标记值.
    // 每次合并都需要查找合并每个元素共N次. 所以进行M次合并 就需要 MN.
    for(t = id[p], i = 0; i < N; i++)
      if(id[i] == t)
        id[i] = id[q];
    printf("%d %d : ", p, q);
    for(i = 0; i < 10; i ++)
      printf("%d ", id[i]);
    printf("\n");
  }
}

/* 
   连通问题 - 快速合并算法
   数据结构: 直接使用线性表 - 数组 - 树形描述连通(逻辑结构).
       index 代表某个 对象
       id[index] 代表对象连通到另一个对象, 
         id[index1] == index2, 代表 index1 连通到index2.index2是index1的父连通对象.
         id[index] == index， 表明对象连通到自己, 自己就是根对对象.
     当多个对象的连通根对对象相同, 则对象连通. 这样对象保存的内容使得 合并更加高效.
     这都是怎么想到设计的, 能够那么高效的实现合并.

   算法: 
       查找: 判断两个对象的根连通对象是否是一个.
       合并: 当两个对象不连通, 需要合并, 则直接将前一个对象p, 作为q的子对象进行连通.
   性质:
       对于M>N， 快速合并算法求解N个对象 M个连通问题 需要执行M*N/2次指令.
   优点:
       合并快速, 将p对象的 根连通对象 作为q对象的子对象即可, 因为树形结构具有 父节点管理子节点的能力。所以q连通了p的根对象,那么就连通了所有与p连通的对象.
   缺点:
       查找, 需要进行回溯寻找根连通对象, 速度相对快速查找慢. 这是逻辑实现结构所决定的.
 */
void connect_quick_combine(){
  // id[N] N 个数据点, 原本全部连通.
  // index 是每个数据
  // id[index] 是标记, 两个数据index1 index2 如果连通 那么他们具有相同的树根节点.
  // 
  int i, j, p, q, t, id[N];
  for (i = 0; i< N; i++)
    id[i] = i;
  
  // 每个输入对 判断是否连通.
  while(scanf("%d %d", &p, &q)== 2){
    /*1 查找: 先查找对象自己的 根连通对象(连通集合代表) p - i, q - j.
           如果根连通对象相同,那么两者连通.
     查找操作 指令变多, 寻找树根.
     最坏情况:
        1-2 2-3 3-4 如此进行合并后 查找N的根 需要上溯N-1个指针.
        结果 平均下 1 - N上溯根连通节点时 需要(0 + 1 + 2 + ... + N-1)/N = (n-1)/2
        此时 其他节点a (>N/2) 查找是否连通到b N上, 即每次a 都上溯>N/2个指针 b每次上溯N-1
        这样每次查找操作 都会大于N次(N/2 + N-1) M个查找操作就会大于MN.
        这些都是因为 此时的树是一颗线性表. 所以没有达到树的回溯特性.

    */
    for(i = p; i != id[i]; i = id[i]) ;
    for(j = q; j != id[j]; j = id[j]) ;
    if(i == j)
      continue;
    // 否则不连通进行合并.
    // 2 合并, 直接将p对象的根连通对象i 设为j 的子对象,那么p的根连通对象变为了q的根连通对象 连着连通.
    // 每次合并 只需要1条指令.
    id[i] = j;
    printf("%d %d : ", p, q);
    for(i = 0; i < 10; i ++)
      printf("%d ", id[i]);
    printf("\n");    
  }
}

/*
  加权快速合并算法
  是快速合并算法 为了加快查找的改进.
  普通快速合并算法 直接将第一棵树 安排到第二棵树上,没有进行判断择优,
     导致树深度无节制加深,查找时遍历深度导致速度变慢
  通过增加 sz[] 数组保存当前某个对象的树结构大小, 当连通两个对象时, 将较小树连通到较大树的根连通对象。
    这样操作, 会保证树深度不会太深, 这样减少查找时的根对象搜寻时间.
    数据结构-数组:
        index 代表 对象
        id[index] 代表连通到的父对象, 当index == id[index] 则index 是某个连通树的根连通对象,用来判断.
        sz[index] 本根连通对象的树规模大小,
    性质:
        对于N个对象, 加权快速合并算法判断两个对象是否连通, 最多需要遍历2*lgN个指针.
        当合并操作进行时, 发生 待合并的数据集树大小总是一样大时, 出现最坏情况,
    在合并两棵2^n大小的树时,到达根连通对象需要n次深度遍历。而对于普通未加权合并算法
    最坏情况2^n大小的树, 到达根连通对象需要 2^n - 1次 深度遍历.所以对于速度提升明显.

    优点:
        加权记录树深度,有效限制树深度的加深, 数据规模变大,影响也不大.
    缺点:
        增加记录 树深度的结构sz[]. 说明为了时间复杂度 需要修改数据结构 记录算法需要的新数据,改变空间复杂度.

 */
void connect_weight_combine(){
    int i, j, p, q, id[N], sz[N];
    for(i = 0; i < N; i++){
        id[i] = i;
        sz[i] = 1;
    }

    while(scanf("%d %d", &p, &q) == 2){
        for(i = p; i!= id[i]; i = id[i]) ;
        for(j = q; j!= id[j]; j = id[j]) ;

        if(i == j)
            continue;

        //只需要记录 根连通对象即可, 以后任何查找
        //实际上都找到的是根连通对象, 其他对象没有作用.
        /*
        增加权重判断后 树的生成形状会大有不同, 上溯到根节点的距离是 节点的log2函数.
        2^n节点的树 上溯到根节点需要n个指针回溯, 由此 查找操作变得很轻松.
        O(2log(N))的时间复杂度.
        */
        if(sz[i] < sz[j]){
            id[i] = j;
            sz[j] += sz[i];
        }else{
            id[j] = i;
            sz[i] += sz[j];
        }
        printf("%d %d : ", p, q);
        for(i = 0; i < 10; i ++)
          printf("%d ", id[i]);
        printf("\n");
    }
}


void connect_weight_path_half_compression_combine(){
    int i, j, p, q, id[N], sz[N];
    for(i = 0; i < N; i++){
        id[i] = i;
        sz[i] = 1;
    }

    while(scanf("%d %d", &p, &q) == 2){
        /*遍历寻找根连通对象过程中, 进行等分路径压缩. 每次查找都进行路径压缩*/
        for(i = p; i != id[i]; i = id[i])
            id[i] = id[id[i]];
        for(j = q; j != id[j]; j = id[j])
            id[j] = id[id[j]];

        if(i == j)
            continue;

        if(sz[i] < sz[j]){
            id[i] = j;
            sz[j] += sz[i];
        }else{
            id[j] = i;
            sz[i] += sz[j];
        }

        printf("%d %d : ", p, q);
        for(i = 0; i < 10; i ++)
          printf("%d ", id[i]);
        printf("\n");
    }
}

void main(){
//    connect_quick_find();
//    connect_quick_combine();
//    connect_weight_combine();
    connect_weight_path_half_compression_combine();
}


/*
 * 总结:
 *  算法是实现目标结果的操作步骤方法.
 * 算法的处理对象就是 目标数据. 而目标数据 结构 怎么组织 就是数据结构.
 * 数据结构要适应算法, 当算法应用到有结构的数据上时, 不同的数据结构肯定适配不同的算法这样才能高效.
 * 算法 一般就是 查找 替换 合并 删除等等。
 * 而查找:
 *   对 线性存储的数据结构 就是索引, 最快.
 *   对 链表存储的数据结构 就是指针遍历, 速度缓慢.
 *   对 树形结构存储的数据 那么可以通过树形深度遍历, 并且跟树形组织方式, 也要指针遍历,但是速度比 链表高效的多得多.
 * 而对合并
 *   对 线性存储的数据结构 那就需要遍历所有想关数据. 速度缓慢
 *   对 链表存储的数据结构 只需要将链表头 加入到目标即可
 *   对 树形结构存储的数据 和链表式结构差不多。
 *
 * 结论是:
 *   算法的实现是需要 数据结构支持的
 *
 *
 */