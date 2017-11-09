#include "heap_index.h"
/* 
   1   data[] 元素数组，不用移动数据， 通过pd索引堆即可以实现堆序访问。
   
   2   pd[]  索引堆，保存的value不是堆序关键字，但是可以通过value得到关键字。
       index: 堆序 1 的key 要大于 2 3 的key
       value: 数据的索引index，用pd的value来索引数据获得关键字 形成堆优先性

   3   map[] 数据index反向索引pd
       当data数据改变时，pd索引堆，并不会知道哪个元素被改变了，所以就无法进行fixup fixdown。 因为pd保存了 data的索引， 但是当data数据改变时，pd并不知道。 所以就需要有人通知pd它的哪个关键字值改变了。 即 data －map－ pd 再反向映射到pd，通知pd关键字的改变。
       index：data元素的index data－map
       value：保存的pd的索引，data如果某个元素 data[i] 发生改变 通过k ＝ map[i]即可得到需要 pd[k] 需要堆化。

    堆（heap）是一种常见的数据结构，经常用来实现优先队列。其中最常见的是二叉堆（binary heap）。由于它特殊的性质（二叉满树）所以可以用数组高效的实现。
    堆还能用来进行排序，堆排序（heap sort）具有快速（复杂度O(N * logN)），稳定的特点，尤其是非常稳定，因此适用于某些需要排序稳定性的场合。
    
But，普通的二叉堆有两个缺陷：
    1，在堆中的元素体积非常大的情况下，经常性的移动元素是低效的。
    2，如果在堆的使用过程中，堆中的元素的值要改变，则普通堆对此无能为力。简单的说，一个元素如果进入堆之后，它的值就不能改变了，否则会影响堆的性质。
    第一个缺陷还能用类似指针排序的技术解决，但是第二个缺陷不采用特殊的技术是没办法解决的。然而在一些场合，堆中元素的值确实需要改变。因此索引堆（index heap）闪亮登场~~
    所谓索引堆，简单地说，就是在堆里头存放的不是数据，而是数据所在数组的索引，也就是下标（本文中索引和下标是一个意思，互相换用），
    根据数据的某种优先级来调整各个元素对应的下标在堆中的位置。本质上来说索引堆也是堆，提供堆的接口。由于索引堆最终用来实现优先队列，所以又可以叫索引优先队列（index priority queue）。接下来就说明索引堆的实现，以及为什么索引堆能解决刚才说的两个缺陷。
    -----------------------索引堆如何实现？------------------------

    因为索引堆也是堆，所以其实只要实现了上滤（fix up）和下滤（fix down），基本上就实现了整个堆。
    但是索引堆建立了两重映射，所以实现上滤和下滤的时候必须小心翼翼，否则很容易出错。注意到一个索引经过两次映射之后会映射回自己，即
    pq[map[i]] = map[pq[i]] = i
    这个性质很重要，因为这是保证索引堆有效的条件。必须满足这一点，索引堆才能正常使用。因此上滤和下滤的过程中，除了要保证堆本身的性质，还必须保证索引的性质。只要满足了这两个性质，程序就是正确的。

    http://blog.sina.com.cn/s/blog_4dff87120100su10.html
*/

#define Parent(x) x/2
#define LeftChild(x) 2*x
#define RightChild(x) 2*x+1

static int N= 0;
static int *pq;
static int *map;

/*
  1 PQ 堆函数 使用的参数 是 索引堆pq_index. 因为pq才是实际堆,
    而它的关键字值保存在data中, 需要间接获得而已
  2 map 需要反向索引到pq, 这样当改变data内关键字值时, 才能通知pq对对应的值进行堆化.
*/

//向上堆化 
/*
 找到父节点，进行比较(Priority(i, parent)), 判断是否进行交还, 堆序 索引数组
 i 索引堆的index，内容使实际数据data的index  */
void FixUp(int i){
  int curr, parent, index = pq[i];
  /* 1 curr parent
     2 条件：
        1 parent >= 1  索引数组从1开始的。   必需要大于
        2 Priority(curindex, parentindex) 关键字值大，才进行堆化
     3 进行 parent 作为当前需要向上堆化。parent的parent就是下一个
   */
  for(curr = i, parent = Parent(i); 
      parent >= 1 && Priority(index, pq[parent]);
      curr = parent, parent = Parent(parent)){
    /* 
       使用空穴方法 先保存最终需要的值，过程中需要交换的都先向后进行，保留空穴 
       pq[curr] 被赋值 pq[parent]
          就是 pq[parnet] 被移动 原本的pq[parnet] 位置的数据没用了 可以被每次循环与目标值交换， 或者就是用空穴方法 作为空穴。
     */
    pq[curr] = pq[parent];
    /* 
       反向引用数组 保证能够正确反向引用到pq
       pq[pqindex] == dataindex,
       map[dataindex] == pqindex
     */
    map[pq[curr]] = curr;
  }
  /* 
     最终空穴 需要被赋予 最终值
     使用空穴方法能够减少赋值操作
  */
  pq[curr] = index;
  map[pq[curr]] = curr;
}



void FixDown(int i){
  int curr, child, index = pq[i];
  for(curr = i, child=LeftChild(i);
      child <= N;
      curr = child, child = LeftChild(child)){
    /* 
       1 right child is available 
       2 then judgement the priority(left and right)  
       then child = right child;
    */
    if(RightChild(curr) <= N && Priority(pq[RightChild(curr)], pq[child]))
      child = RightChild(curr);
    
    if(Priority(index, pq[child]))
       break;

    pq[curr] = pq[child];
    map[pq[curr]] = curr;      
  }
  pq[curr] = index;
  map[pq[curr]] = curr;
}

  

/* 
   上滤和下滤虽然很重要，但我也不多说。
   如果熟悉堆的性质，并且了解了索引堆的思想，那么代码是不难看懂的。
   然后是索引堆的接口
*/


/*
 PQinit用数据数组元素的最大个数作为参数来初始化索引堆，
    实际上就是给两个数组pq和map分配内存，并将N设置为0
*/

void PQinit(int n) {
  pq = malloc((n+1) * sizeof(int));  // 优先队列从下标从1开始
  map = malloc(n * sizeof(int));
  N = 0;
}

 

/*
 PQinsert将数据插入到堆，注意插入的不是实际的数据，而是数据的索引，
    参数i也就是被插入元素在数组中的下标。被插入的元素刚开始放在堆的末尾，因此插入后进行一次上滤就可以了
*/
void PQinsert(int i) {
  pq[++N] = i;
  map[i] = N;
  FixUp(N);
}

 

/*
 PQdelmax将堆中第一个元素取出来，这个元素所对应的数据拥有最大的优先级。
    注意此处的max是抽象的max，并不是说最大的元素，而是拥有最大优先级的元素。
    为了保持堆化，将最末尾元素放到第一位进行一次下滤即可
*/
int PQdelmax() {
  int max = pq[1];
  pq[1] = pq[N--];
  map[pq[1]] = 1;
  FixDown(1);
  return max;
}

 

 

/*
 PQchange就是为了解决第二个问题，当数据数组中的元素改变时，
    调用这个函数即可将改动反应到堆中并保持堆的性质，参数i是改动元素的下标。
    用map可以将数据数组映射到pq，实现非常简单
 i: data_index
 PQchange(data_index)
*/
void PQchange(int i) {
  FixUp(map[i]);
  FixDown(map[i]);
}

 

/*
 PQempty检测堆是否是空的，只需检测N是否等于0即可
*/
int PQempty() {
  return N == 0;
}

 

/*
 实现了上述5个接口，以及优先级函数Priority，就可以使用索引堆了。
    我在这里展示如何用索引堆将一个数组中的元素按照大小顺序打印出来
*/
/*
 -----------------------总结------------------------

    与普通二叉堆相比，索引堆本身也有两个不算缺点的缺点：
    一，实现稍微复杂；二，因为开辟了两个数组pq和map，因此需要占用更多空间。
    但索引堆近乎完美地解决了普通堆了两个缺陷，这两个缺点就显得微不足道了。
    索引堆在解决图算法的最小生成树（minimum spanning tree）和 最短路径（shortest path）问题中都有很优雅的应用（这也就是为什么我会知道这个东西- -。。。）最小生成树和Prim算法的索引堆实现和最短路径的Dijkstra算法的索引堆的实现几乎一模一样~。
*/
