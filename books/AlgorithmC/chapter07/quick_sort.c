#include "quick_sort.h"

/*
7.1 基本快排实现, 以及可能问题
1 重复元素
*/
int partition(Item a[], int l, int r)
{
    // 算法循环时需要+1
    int i = l-1;
    int j = r;
    // 直接从末尾选取划分元素, 进行划分a, 最终将a[r] 放到其排序最终位置.
    Item v = a[r];

    for(;;){
        //找到 a[i] > v;
        // 一直++ 也不会越界, 因为 v == a[r]. a[r]就是观察哨.
        while(less(a[++i], v)) ;
        //找到 a[j] < v;
        // 没有观察哨.
        while(less(v, a[--j]))
            //说明从右遍历 都是比 v大的. a[r] 就是文件中最小元素.直接跳出.
            //如果v 最小, 那么一直循环,因为没有观察哨, --j, 会发生越界, 所以需要判断是否到边界.
            // ！！ 快速排序内部循环很小, 这个检测会对性能带来影响. 以后学习避免使用这个判断
            if(j == l)
                break;
        //当 左右指针 相遇, 说明本次分治划分结束, a[r]的最终位置已经找到,
        //并且使用i 将a[]分治划分为两个子文件
        if(i >= j)
            break;

        //到达此处说明,
        //1 当i j没有相遇
        //2 左侧 和 右侧 对于v有一对逆序需要交换, 使得文件有序.
        exch(a[i], a[j]);
    }
    //i 和 j 已经相遇(从i 向右都>a[r], 向左都<a[r] )
    //并且 a[i] 是一个>a[r]的元素, 和a[r]直接交换, 那么整个文件 对于a[r]->a[i]来说已经是有序的了.
    //剩下就是进行子文件递归如此排序.
    exch(a[i], a[r]);
    return i;
}

void quick_sort(Item a[], int l, int r)
{
    int i;
    //一个文件排序完成的条件: 子文件只有一个元素.
    if(r <= l)
        return ;

    //分治划分待排序文件 为两个子文件
    // 两个子文件 被 a[i] 分治划分, 并且对于 a[i] 有序.
    // a[i] 位置就是最终位置.
    i = partition(a, l, r);
    //分治排序两个子文件
    quick_sort(a, l, i-1);
    quick_sort(a, i+1, r);
}

/*
 快排 当遇到重复元素时, 会被影响性能. 怎么影响?
//          使用基本的partition 感觉不会影响 不过就是浪费了下进行了一次交换.
//有三种策略来处理 指针遇到重复元素问题:
// 1 两个指针都停止, 这个策略最好, 但是那怎么进行分治划分呢?
// 2 一个停止 一个 继续扫
// 3 两个都继续扫描.
*/

/*
7.2 快排的性能特性
    NlogN的时间复杂度
*/

/*
7.3 栈大小
 栈方式实现 快排.
*/
void quick_sort_stack(Item a[], int l, int r)
{
    int i;
    stack_init(100);
    push2(l, r);

    while(!stack_empty()){
        l = stack_pop();
        r = stack_pop();
        //此待排序数据 已到达最底, 不需要继续排序.
        if(r <= l)
            continue;
        i = partition(a, l, r);
        //将大的分治子文件先入栈, 保证后入栈的文件规模小, 当继续下一个循环时 会将该小规模文件
        //分治, 继续分半入栈, 这样 栈就是一个LogN规模的大小的.
        //因为最底的元素值 CN 在上一个就是 CN/2 时logN的增长.
        if(i - l > r - i)
        {
            push2(l, i-1);
            push2(i+1, r);
        }else{
            push2(i+1, r);
            push2(l, i-1);
        }

    }
}

/*

 7.4 小的子文件
 通过观察, 递归程序调用自身 会产生会多分治子文件, 而快排对于小文件排序可能能够改进.
 1 if(r -l < M)  insert_sort(); 对小文件都使用插入排序
 2 if(r -l < M)  return ; 对小文件就不再排序了, 然后在最外层 使用 插入排序,
    因为此时 快排已经使序列近似有序了, 所以可以使用插入排序提升速度 提升 10%
    M 一般选择 5 - 25 一般就是 10就OK了.




*/

/*
 7.5 三者取中划分元素法
 划分元素的选择十分重要, 直接影响快排效率.
 三者取中法 就是选择 三个元素 选择其中 中间值的元素, 进而改进:
 1 使得快排的最坏情况几乎不可能发生。
 2 减少了 划分对观察哨的需要.
 3 提高运行时间, 因为总是用抽样取中的元素, 满足快排对于元素在中间的需求.
 三者取中 + 小文件使用插入排序 能够提升 算法20%的效率
 */
#define M 10
void _part_of_quick_sort_pro_M_return(Item a[], int l, int r){
    int i;
    if(r - l <= M)
        return ;

    //这样 经过三者取中, 对于 a[r-1] a[l] a[r] 就是观察哨.
    exch(a[(l+r)/2], a[r-1]);
    compexch(a[l], a[r-1]);
    compexch(a[l], a[r]);
    compexch(a[r-1], a[r]);

    i = partition(a , l+1, r-1);
    quick_sort_pro(a, l, i-1);
    quick_sort_pro(a, i+1, r);
}

void quick_sort_pro(Item a[], int l, int r){
    _part_of_quick_sort_pro_M_return(a, l, r);
    insert_sort_pro(a, l, r);
}

/*
7.6 重复关键字
使用三路划分方式
1 左端 等于划分元素的值, 交换到数组最左端
2 右端 等于划分元素的值, 交换到数组最右端

*/
void quick_sort_for_multi_same(Item a[], int l, int r){
    int i, j, k, p, q;
    Item v;
    if(r <= l)
        return  ;
    v = a[r];
    //  l-1 是为了下面算法方便使用, 先-1 后面同一都是++ 后使用
    i = l - 1;
    p = l - 1;
    j = r;
    q = r;

    for(;;){
        while(less(a[++i], v))  ;
        while(less(v, a[--j]))
            if(j == l)
                break;
        if(i >= j)
            break;
        //换位.
        exch(a[i], a[j]);
        //如果相等, 则将a[i] 与p位置元素换位, 这样将所有v相同元素都弄到左子文件最左.
        // 等划分完毕, 再讲这些元素都交换到左子文件最右 满足排序.
        if(eq(a[i], v)){
            p++;
            exch(a[p], a[i]);
        }
        if(eq(v, a[j])){
            q--;
            exch(a[q], a[j]);
        }
    }
    exch(a[i], a[r]);

    //将l-p 与划分元素值相等的元素 从左子文件的最开始 换位到 左子文件的最末尾.
    //l -> i-1, <-> j-i+1 -> j;
    j = i - 1;
    for(k = l; k < p; k++, j--)
        exch(a[k], a[j]);

    i = i + 1;
    for(k = r-1; k > q; k--, i++)
        exch(a[k], a[i]);

    quick_sort_for_multi_same(a, l, j);
    quick_sort_for_multi_same(a, i, r);

}


/*
 7.7 字符串和向量
 对于 字符串数组排序,  完全可以使用6.11 使用
typedef char* Item;
#define less(A, B) strcmp(A, B)
使用strcmp 比较两个元素, 而strcmp 比较字符串 会逐个比较每个字符, 如果字符都近似相同时, 那么开销很大.
eg
    discreat discredit discrete discrepancy discretion 这样的文件, 这些字符串比较, 必须到第7个字符才能比较出顺序.
    ？？？如果我们知道前6个字符相等的信息, 我们完全可以从第7个字符开始比较, 但是这个信息是不可知的啊.???

    第十章 会考虑大量排序的技术, 利用 排序关键字被分解成小部分的事实.
    这种问题 就是 多维排序问题, 被排序的关键字 可以使向量,
    是个重要应用........
 *
 */

/*
7.8 选择
一个与排序有关 但是又不需要完全排序的应用
找出一组数的 中间数
时间复杂度: O(lgN)
eg
    例如找到排序后第x位置的数, 每次递归分治划分 平均 划分N/2
    ... 具体怎么算还要看
*/

void quick_sort_select(Item a[], int l, int r, int k){
    int i;
    if(r <= l)
        return ;
    i = partition(a, l, r);

    if(i > k){
        quick_sort_select(a, l, i-1, k);
    }
    if(i < k){
        quick_sort_select(a, i+1, r, k);
    }
}

void quick_sort_select_no_recurise(Item a[], int l, int r, int k){
    while(r > l){
        int i = partition(a, l, r);
        if(i > k)   r = i-1;
        if(i < k)   l = i+1;
        if(i == k)
            return ;
    }
}



int main(int argc, char* argv[]){
    Item a[1000];
    int i = 0;
    for(i = 0; i < 1000; i++){
        a[i] = rand()%1500;
    }
    quick_sort_for_multi_same(a, 0, 999);

    for(i = 0; i < 1000; i++){
        printf("%d  ", a[i]);
    }
    printf("\n");
}


