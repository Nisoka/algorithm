#ifndef ITEM_STRING_H
#define ITEM_STRING_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//关键字               元素
//用来比较的数据信息     实际数据

#define ABSTRACT_POINTER_SORT
//#define ABSTRACT_INDEX_SORT
/*
 6.6 索引和指针排序
string 要比int float 等基本数据类型更有挑战性,
 因为C使用字符串时, 我们必须注意对字符串的内存分配.


指针排序
    因为C中 字符串时使用 char* 表示, 所以程序可以是一个 指针排序
    char* data[];
    eg char* argv[], 每个argv[n] 都是一个字符串
    指针数组
        pointer[i] = &data[i]
        *pointer[i] 直接可以索引到元素,
        而data内容保持不变, 进行排序时,
        1 less 使用 *pointer[i] *pointer[j]
        2 exch 使用 exch(pointer[i], pointer[j])即可
        排序后 *pointer[i] 就是有序的数据排列

    指针排序更具有一般性,
        指针可以指向任意元素 并且不限制元素大小. 标准C的qsort就是一个指针排序.
        只需要实现对应的less (可以指定自己想要的排序规则) 以及exch (交换的只是指针) 即可
        交换的只是指针, 这样实际数据不需要移动, 在排序文件时 极其重要.


索引排序
    类似字符串这样的数据, 进行排序时, 并不希望排序实际对象, 而是希望排序他们的索引.
    通过索引 就可以得到不同的数据元素.
    而字符串的实际保存内存地址 并不移动.
    索引数组
        这样就需要使用一个 索引字符串的数组. a[i], 其中保存着 索引数据元素的index.
        data[id[i]]
        1 less 使用 data[id[i]] data[id[j]]
        2 exch 使用 exch(id[i], id[j])即可
        排序后, i 顺序 data[id[i]] 就是有序的.

*/

typedef char* Item;

#define key(A) (A)

#ifdef ABSTRACT_POINTER_SORT
//#define less(A, B)  (strcmp(key(A), key(B)) < 0)
#define less(A, B)  (compare(A, B))       //比较的是数据元素
#define exch(A, B)  {Item t = A; A = B; B = t;} //排序的是指针(引用对应元素)数组
//这里 A B 就是 pointer[i]
int compare(void *i, void *j);
#else

//data 保存数据元素(指针)
//id 保存data中不同对象的索引, 原始 id[i] = i; 一一顺序对应 data[id[i]] = data[i]
//排序后 data[id[i]] 就是按顺序进行了.
// 实际上比较是通过data比较, 但是操作 是操作id[i]
#define less(A, B)  (compare(data[A], data[B]))     //比较的是数据元素
#define exch(A, B)  {Item t = A; A = B; B = t;}     //排序的是索引(索引对应元素)数组
//这里 A B 就是 id[i]
#endif

Item item_rand();
int  item_scan(Item *v);
void item_show(Item v);

/*
使用下标或者指针排序的主要原因
 1 避免扰乱所要排序的数据
    可以排序只读文件, 可以更自由的实现比较函数 less (可以尝试不同比较方法)
 2 避免移动数据
    有时候数据比较大, 那么移动的代价很大.

    很多时候不需要数据在物理上重排成有序, 只需要我们能够有序的访问即可.
如果确实需要物理有序的话, 对于大数据,也不应该直接排序文件, 而是可以通过先下标排序, 然后进行元素拷贝.
    for(i = 0; i < N; i++) datacp[i] = data[id[i]]
*/

//原位排序, 不理解.
//间接排序(指针排序、索引排序) 需要额外的空间来存储下标数组 或 指针 数组, 以及额外的比较时间。但是比起移动数据, 间接排序灵活性更强, 如此对比, 这些开销完全值的. 尤其对于移动大小比较大的数据文件, 我们几乎总是使用间接排序.



#endif // ITEM_STRING_H
