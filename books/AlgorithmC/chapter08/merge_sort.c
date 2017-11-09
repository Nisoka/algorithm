#include "merge_sort.h"

//8.1 两路归并
//将已经有序的 a b 归并到c中
void merge_ab(Item c[], Item a[], int N, Item b[], int M)
{
    int i, j, k;
    for(i = 0, j = 0, k = 0; k < N+M; k++){
        //a 全部归并完
        if(i == N){
            c[k] = b[j++];
            continue;
        }
        //b 全部归并完
        if(j == M){
            c[k] = a[i++];
            continue;
        }
        //使用less
        // 1 可以定制自己的规则
        // 2 a的意义可以自己考虑(可以是指针、可以是索引、也可以是元素、还可以是元素的关键字)
        c[k] = (less(a[i], b[j])) ? a[i++] : b[j++];
    }
}

/*
8.2 抽象原位排序
bitonic 序列 在中间形成观察哨.
*/
#define maxN 1000
Item aux[maxN];
void merge(Item a[], int l, int m, int r){
    int i, j, k;
    //复制a 到 aux, 最后在m 处, 是最大值所在位置, 形成观察哨.
    //从m -> l, 最后i == l.
    for(i = m+1; i > l; i--)
        aux[i-1] = a[i-1];
    //从m -> r, 最后j = r, 而aux里m-j的副本是倒序的.
    for(j = m; j < r; j++)
        aux[r+m-j] = a[j+1];

    for(k = l; k <= r; k++){
        //不用考虑数组越界问题, 此时中间m 就是观察哨了.
        if(less(aux[j], aux[i]))
            a[k] = aux[j--];
        else
            a[k] = aux[i++];
    }
}

/*
 * 8.3 自顶向下归并排序
// 自顶向下, 是解决问题的一个分治范型方法, 将问题整体 逐渐划分, 考虑问题整体是顶, 当逐渐划分到最底层时,
// 完成整个问题处理, 这就是自顶向下逐渐解决问题.
*/
void merge_sort(Item a[], int l, int r){
    int m = (r+l)/2;
    //结束条件, 认为只有一个元素是 是最 底 的问题被解决, 一个元素就是被排好序了.
    if(r <= l)
        return ;
    merge_sort(a, l, m);
    merge_sort(a, m+1, r);
    //抽象原位归并排序 问题的解决是自底向顶的.
    merge(a, l, m, r);
}

//归并排序很重要, 是最理想的直接排序方法.
//归并排序 是 以归并操作为基础的排序算法. 归并就是讲两个有序的文件 合并为一个有序文件.


/*
 8.4 基本归并算法的改进pro
 1 对于小文件 使用 插入排序来提升效率 提升10%(至少)
 2 消除归并操作时, 将原数组复制到辅助数组 所花费的时间。
    为做到这一点, 我们切换每次 输入数组a 和 辅助数组aux 的作用, 互相切换.
    达到没有 复制的归并排序.
*/
void merge_sort_ABr(Item a[], Item b[], int l, int r){
    int m = (l+r)/2;

    //最底排序 使用插入排序方法.
    if(r-l<10){
        insert_sort(a, l, r);
        return ;
    }

    merge_sort_ABr(b, a, l, m);
    merge_sort_ABr(b, a, m+1, r);

    // 最后一步, 是 归并b+l, b+m+1 到a+l
    // 所以通过自顶向下递归的执行, 只要保证最顶的a 是输出数组, b是辅助数组即可 , 与汉诺塔问题一样
    merge_ab(a+l, b+l, m-l+1, b+m+1, r-m);
}

void merge_sort_AB(Item a[], int l, int r){
    int i;
    for(i = l; i < r; i++){
        aux[i] = a[i];
    }
    merge_sort_ABr(a, aux, l, r);
}

//归并排序 总体比 快排 慢 25% , 通过改进算法, 归并排序能够提升40% 左右.

/*
 8.5  自底向上的归并排序
 5章已经说了, 所有的递归程序都有一个等价的非递归实现, 而计算顺序不同.
 作为分治法的算法实例范型, 归并排序的非递归实现很值得详细研究.
 3章 说 非递归算法 可以通过显式栈 来得到相同的递归算法.
 递归排序 的递归序列 是由描述问题的分治树决定的: 后序遍历访问整棵树, 对子节点排序, 对父节点归并.
 使用层序遍历方法 就得到了自底向上的非递归 归并排序
*/
/*
 按照自底向上的方式思考时, 值得按照组合-求解策略求解问题.
 先求出小问题的解, 通过组合得到大问题的解.
 而组合-求解法 是相对于 分治法的另一个 算法范型.
*/
void merge_sort_BU(Item a[], int l, int r){
    int i, m;
    /*
    每次循环 任务由小变大. 组合求解过程.      1-1 x8      2-2 x4      4-3 x2      8-7
    组合求解算法 要先了解问题的规模 或者说 递归公式 CN = 2CN/2 + N, 才可以实现
    而分治法 则是 通过直接实现, 来了解问题规模递归公式.
    */
    for(m = 1; m <= r-l; m = m+m){
        //每次任务
        for(i = l; i <= r-m; i += m+m){
            merge(a, i, i+m-1, min(i+m+m-1, r));
        }
    }

}

