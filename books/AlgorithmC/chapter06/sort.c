#include "sort.h"


/*
6.2 选择排序 比较实用
选择排序 可以 改名为 选择交换排序
时间复杂度 less 执行次数 N*(N/2) 即O(N^2)
优点, 移动步骤最少, 当对大文件 小关键字的数据进行排序最适用。
缺点, 遍历次数是固定的, 没有利用到 数据序列中的已有顺序 非适应性排序.
*/
void select_sort(Item a[], int l, int r){
    int i, j;
    int minIndex;
    /*
    i 从start开始 a[i] 就是待排序元素
     将a[i] 与内循环i+1 -> r中元素 逐个比较找到的最小的a[minIndex] 进行交换,
     随着i 从start->end, 左边的序列已经变得有序不需要再被访问,
        每次循环后 前面的(l - i) a已经有序不需要再考虑.
     当到达end 排序就完成了.
    */
    for(i = l; i < r; i++){
        minIndex = i;
        //i之前的数据已经有序
        for(j = i+1; j < r; j++){
            if(less(a[j], a[minIndex]))
                minIndex = j;
        }
        exch(a[i], a[minIndex]);
    }
}

/*
6.3 基本插入排序 不实用
非适应性算法???
什么是适应性? 适应性是 适应数据本身的有序性.
比较多, 移动多. 时间复杂度大.
*/
void insert_sort(Item a[], int l, int r){
    int i, j;
    //从start开始到结束
    //循环中 start -  i 已经有序.
    //每次待插入元素a[i]
    for(i = l+1; i <= r; i++){
        //将i 向有序序列中插入, 使得 start -> i 更有序.
        //循环向前比较插入
        for(j = i; j > l; j--)
            //向有序序列 插入.(可以优化, 这里实际上也是冒泡思想)
            //compexch(a[j-1], a[j]);
            if(less(a[j], a[j-1]))
                exch(a[j], a[j-1]);
    }
}

/*
插入排序的改进1
    因为start - i 已经有序, 那么如果插入比较时, less(a[j], a[j-1]) false,
那么 就不需要继续向前进行less(a[j], a[j-1]) 比较 交换.
    这个比上面的排序提升了1/2.
    此时 算法已经使用了数据的本身顺序, 已经是适应性的插入排序.
*/
void insert_sort_pro(Item a[], int l, int r){
    int i, j;
    //待插入元素a[i]
    for(i = l+1; i <= r; i++){
        //每次循环向前比较插入
        for(j = i; j > l; j--){
            if(less(a[j], a[j-1])){
                //向前插入操作.
                exch(a[j], a[j-1]);
            }else{
                break;
            }
        }
    }
}

/*
 插入排序的改进 2
 1 空壳位法:
    保存带插入元素v = a[i], 设定起始点j = i;
    判断less(v, a[j-1]) , 则向后赋值 a[j] = a[j-1], 留下空壳位.
    每次赋值留下空壳位 允许让元素插入或者下次循环将前一个元素继续赋值, 前一个元素位置变为空壳位
    这样去掉了 每次位置交换的不必要操作(局部冒泡), 循环向后赋值, 得到空壳位 提升算法性能.

 2 观察哨改进方法
 观察哨的作用是:
    原本你要讲一个元素插入开头, 你需要确定该元素是已知的最小。
    允许你 使用while() 来代替for, 清晰 易于理解循环目的
    使用观察哨可以保证达到观察哨 必然循环会停止. 不用担心超出.因为观察哨是数据极值.

 这个插入排序 比基本插入排序 快2倍.

 总结:
    适应性插入排序 的运行时间 与 输入文件数据的原始排序有很大关系.
    当数据有一些顺序时, 插入排序要快于选择排序.
*/
void insert_sort_sentinel(Item a[], int l, int r){
    int i, j;
    //小的在前进行一次 从未到头的冒泡, 观察哨冒泡到a[l]
    for(i = r; i > l; i--)
        compexch(a[i-1], a[i]);
    //待插入元素a[i]
    for(i = l+2; i < r; i++){
        j = i;
        //v 待插入元素.
        Item v = a[i];
        //循环向前比较, 插入.
        /*
        向前逐个元素比较大小,
        //v如果小于前面的, 则可以向前, 则将前面的一个向后赋值.
        //还可以向前, 就继续将前面的一个向后赋值.
        // 1 3 4 2, i = 3. j = i = 3; v = 2 就是待插入数据
        // 第一次 while v < 4 则进入循环 a[j] = a[j-1]; j--;
        // 1 3 4 4  此时j = 2, a[2] = 4
        // 第二次 while v < 3 则进入循环 a[j] = a[j-1]; j--;
        // 1 3 3 4  此时j = 1, a[1] = 3
        // 第三次 while v < 1 错误则跳出循环, 此时j 位置就是上面已经向后赋值的留下的空壳位.跳出 执行a[j] = v
        //      (*已经到达观察哨较小值 肯定不能继续前进了*)
        // 1 2 3 4
        */
        while(less(v, a[j-1])){
            a[j] = a[j-1];
            j--;
        }
        a[j] = v;
    }
}

/*
6.4 冒泡排序, 简单 可以优化,
1 适应性的适应 数据原本顺序
2 可以两方向冒泡 提升速度
*/
void bubble_sort(Item a[], int l, int r){
    int i, j;
    //冒泡终点位置, 每次循环, 终点位置减少, 最终排序完成
    for(i = l; i < r; i++){
        //冒泡起始 到 终点
        for(j = r; j > i; j--){
            if(less(a[j], a[j-1])){
                exch(a[j-1], a[j]);
            }
        }
    }
}

void bubble_sort_pro(Item a[], int l, int r)
{
    bubble_sort(a, l, r);
}

/*

冒泡排序(由左向右冒泡)
i s -> e
    j s -> e-i     (后面的有序, 不用考虑了(e-i -> e)序列了)

插入排序
i s -> e
    j i -> s       (前面的有序, 选择j 插入到有序的(s - > i)序列中

冒泡是总找到最极点的(在每次循环中逐渐找到的) 放到最后(最前)保证每次都是最终顺序
    冒泡排序 实际上是一种选择排序. 不过是选择的更懒惰, 只要交换即可.
插入是尽可能有序,但不是最终顺序, 然后继续插入使得更有序.

*/

/*

插入排序算法
    核心
    两个循环
    1 获得待插入元素a[i]                   i  s - e
    2 循环向前面已排序的序列 比较插入.       j  i - s
    特点:
        可优化提前停止内部循环, 因为是向前插入到已排序序列, 优化后为适应性算法 速度提升一倍
        哨兵技巧.

选择排序算法
    核心
    两个循环
    1 获得目标位置(最小元素应该位置)                    i s - e
    2 选择最小元素, 与目标位置元素交换, 将最小元素就位.   j i - e
    特点:
        非适应性算法, 移动次数固定 N^2/2
        交换次数为N 较少, 比较实用

冒泡算法
    核心
    两个循环
    1 冒泡终点位置, 每次循环, 终点位置减少, 最终排序完成   i s - e
    2 冒泡操作起始 到 终点                              j e - i
    特点:
        简单, 时间复杂度N^2
        本身冒泡, 会将后面的数据 也进行了非决定性的排序.
        可优化
            1 提前中断外部排序, 性能有提升, 比不上插入排序优化提前中断内部排序.
            2 循环向两个方向冒泡, 可提升速度

*/

/*
6.5 基本排序的性能特征
这些性能特征 是 为不同问题 选择具体排序方法的指导

*/

/*
 6.6 希尔排序
    是特殊的插入排序, 插入排序是N^2时间的算法, 慢的原因是需要进行一个一个的向前插入, 每次只移动一个位置速度慢.
    希尔排序可以通过多次排序, 每次排序的插入移动h多于1个位置, 来让算法先变得稍微有序, 因为插入排序改进后是可以适应数据本身顺序的.
    进行多次近似排序, 每次数据都变得更有序, 当最终使用h = 1时 速度会快很多.

    h 则可以是固定的一些序列. 例如 3*h+1的序列. 1 4 13 ... 最高的移动间隔h < (r-l)/9
*/
void shell_sort(Item a[], int l, int r){
    int i, j, h;
    Item v;
    //得到最高的 移动间隔h
    for(h = 1; h < (r-l)/9; h=3*h+1) ;
    //进行序列 h间隔 的多次插入排序.
    for(; h > 0; h /= 3){
        //待插入元素
        for(i = l+h; i <= r ; i++){
            v = a[i];
            j = i;
            //循环复制, 结束条件
            // 1 j 到达可插入的最开始位置
            // 2 循环向前比较是否可插入, 每次都j 都会到达比较后的确定可插入位置
            //              如果v < a[j] 则执行j = j-h; 执行之后j位置就是v可插入位置了, 直到v >= a[j], j都是可插入位置了.
            while(j >= l+h && less(v, a[j])){
                a[j] = a[j-h];
                j -= h;
            }
            a[j] = v;
        }
    }
}

/*
3. 关键字索引排序
原理

所谓排序，就是要整理文件中的记录，使之按关键字递增(或递减)次序排列起来。
被排序的对象–文件由一组记录组成。记录则由若干个数据项(或域)组成。其中有一项可用来标识一个记录，称为关键字项。该数据项的值称为关键字(Key)。
在待排序的文件中，若存在多个关键字相同的记录,我们希望通过按关键字索引排序，其中关键字是在一个小范围内的整数。
例如：
此处输入图片的描述
1）我们统计不同值的关键字个数分别是多少：6个0,4个1,2个2,3个3.
2）局部统计比其他关键字小的关键字的个数：0个关键字比0小，6个关键字比1小，10个关键字比2小，12个关键字比3小。
3）根据上述统计数作为索引将关键字放到合适位置：在开头0开始放具有0关键字的元素0，根据0，增加指针值，放下一个0关键字的元素3……）；将具有3关键字的元素从位置12开始放起（12个比3小）；以此类推
C程序实现
*/
void keyword_sort(Item a[], int l, int r)
{
    Item b[r-l+1];
    int cnt[M];               //M为关键字的个数
    for(int j = 0; j < M; j++)//初始化个数全0
        cnt[j] = 0;
    for(int i = l; i <= r; i++) //统计不同值的关键字个数，
        cnt[a[i]+1]++;
    for(int j = 1; j < M; j++)//统计比关键字j小的关键字的个数，cnt[j]存储比关键字j小的元素个数
        cnt[j] = cnt[j] + cnt[j-1];
    for(int i = l; i <= r; i++) //按关键字个数索引放到辅助数组b中
        b[cnt[ a[i] ]++] = a[i];
    for(int i = l; i <= r; i++)
        a[i] = b[i-l];
}
//如果要排序的文件很大，使用辅助数组b会导致内存分配问题，可以通过使用原位排序避免使用额外数组完成

typedef void (*func_sort)(Item a[], int l, int r);
func_sort sort = insert_sort_sentinel;

int main(int argc, char *argv[]){
    int i;
    int N = 1000; //atoi(argv[1]);
    Item *a = malloc(sizeof(Item));
    for(i = 0; i < N; i++){
        a[i] = rand()%1000;
    }
    sort(a, 0, N-1);
    for(i = 0; i < N; i++){
        printf("%d ", a[i]);
    }
}

//原位排序, 使用更少的额外空间.
//合适置换 文件的原位排序, 一般极少使用, 针对大文件物理排序使用.
//即使确实需要排序大文件, 也一般使用选择排序进行.
void insitu(Item data[], int a[], int N){
    int i, j, k;
    for(i = 0; i < N; i++){
        Item v = data[i];
        for(k = i; a[k]!=i; k=a[j], a[j] = j){
            j = k;
            data[k] = data[a[k]];
        }
        data[k] = v;
        a[k] = k;
    }
}
