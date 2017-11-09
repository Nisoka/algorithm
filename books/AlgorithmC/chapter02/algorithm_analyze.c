#include <stdio.h>
#include <stdbool.h>


/*
 * 2.1 实现 和 经验分析
 * 分析算法时, 主要考虑的是算法的性能,以及一些关注与算法性能的特征.
 * 对更好性能的算法更感兴趣, 对更简单有效的算法更感兴趣.
 * 理解算法的性能特征 是算法分析的主要目标.
 * 不论是解决大规模问题、系统关键部分的高效实现都　需要高效算法。
 * 而实现高效算法　就需要理解算法　的　性能特征．
 * 1 经验分析
 *   通过直接执行算法, 可以比较算法相差时间进行比较.
 *   而当算法处理的数据规模很大, 算法的实现复杂时.
 *   在算法复杂实现困难时,
 *   希望在花费大代价实现复杂算法之前, 通过进行数学分析 或者 经验分析, 以得到 算法可能有的效率.
 *
 *   当用经验分析 对不同算法进行比较 在不同机器、编译器、或者系统上的实现
 * 或者病态输入的大规模数据时,容易产生错误。
 *   经验性的比较算法的一个危险是 一个算法比一个算法更好.
 *
 *
 * 常用的一种方法是  对解决问题的一个算法进行改进 从而引出新算法.
 更一般的是, 我们试图 明确问题中的 核心重要抽象操作, 并基于这些重要操作上, 对不同算法进行比较。

  选择某个算法的一个常见错误是 忽略算法的性能特征.
    很多简单算法是 2次算法M*N, 而复杂算法又不容易实现, 但是经常的通过改变简单算法的几行代码就可能
得到极大的性能提升而变为 NlogN算法. 而很多人不会使用算法 就会使用简单算法, 忽略时间复杂度.
  第二个错误 是过度的关注算法的性能特征
    当一个部分 并不长被运行时, 或者运行总时间只有几秒 或者几分钟,
复杂算法可能能够提升效率, 但是得不偿失.
 */

/*
 * 2.2 算法分析
    数学分析在比较算法性能的过程中, 所起作用的框架.
    我们将讨论一些用于算法分析的基本数学工具, 以便学习对算法的经典分析方法.理解算法的性能特征。
目的是:
    比较同一任务的不同算法
    预测算法的性能
    设置算法的超参数.

    一般来说 经验分析 就能够评估算法 性能了, 但是数学分析 能够获得更多信息, 并且代价更小.
任务是:
    发现算法性能的尽可能多的信息 是 算法分析的任务.

1  明确算法基于的抽象操作. 从而在实现中 把需要分析的部分分离出来.
2  我们必须要研究输入的数据, 为算法的输入建立模型,
随机数据时的一般性能, 或者伪输入 最坏情况下的性能.


*/

/*
    2.3 描述函数
    描述一个算法的大致运行时间 首项*算法抽象步骤的实现代码指令数目.
首项一般是
    NlogN N^2 N^3 logN 1 N^3/2 .... 中的一个,并且各有自己对应的应用场景



*/

/*
    2.4 大O符号
    算法分析时, 帮助省略数学细节的 符号 --- O()
    定义:
        如果存在常数 C0 N0, 对所有N > N0 都有 g(N) < C0*f(N), 则 称g(N) 是 O(f(N))的.
        (例如 k*x < C0 * x,  O(x) 就 是k * x 的复杂度?).
    作用:
        限制忽略数学公式中的低阶项时产生的误差
        限制由于忽略对程序总运行时间较小的某些部分 产生的误差。
        *允许我们按照算法总运行时间的上界对算法进行分类*.
    含有大O项的表达式 叫做 渐进表达式

    1 约等于:
        当f(N)渐进大于g(N) (也就是 N -> 正无穷时, g(N)/f(N) = 0)
        则术语说 f(N) 约等于 f(N) + O(g(N));

    2 成正比:
        当g(N)渐进小于f(N), 算法运行时间等于 c*f(N) + g(N)时, 则算法的运行时间 与f(N)成正比.



    在N够大时, 大O符号提供了 不用考虑 一些繁杂小项的近似答案.

*/

/*
    2.5 基本递归方程
    本章节都是为了计算 算法运行时间的. 所以说的递归方程也是 求解算法运行时间的方程.
    算法都是有各个步骤组成的, 而算法 一般也都是由循环迭代构成的, 迭代就会发生 逐次减少迭代大小的过程
    算法运行时间 就是一个递归方程.
*/

/*
    2.6 算法分析示例.
    顺序搜索 和 二分搜索. 都是查找对象是否在一个集合中.

    比较算法的一般操作:
        1 利用数学分析 找出算法执行关键抽象操作的频率
        2 利用这些结果导出运行时间的函数式
        3 最后验证 并 扩展经验分析结果.


*/

/*
    2.7 保证 预测 和 局限性
    很多算法 是依赖 输入数据的, 但是我们尽量消除这个相关性.尽可能的减少算法对输入数据的依赖.
    最坏情况分析
        对算法性能 运行时间 的保证。
        但有时候不需要过度考虑 最坏情况分析, 因为这会消耗大量时间,但是这个保证虽然提高但是 实际情况
    很少有最坏情况发生.例如带路径压缩的的加权快速合并 比 普通的加权快速合并 保证要好, 但是实际使用中
    两个算法对同一个一般数据 运行时间相同.

    平均情况分析.
        能够预测算法的运行时间.




*/










/*大于log2N的最小整数.
 log2N 就是求解 2^x = N 中的x
 即 2*2*2*2 ... = N, 所以求解x就是N多次除2, 当整除为0时,得到大于log2N的最小整数.
 */
int get_lgkN_value(int inputN, int k){
    int lgkN = 0;
    for(lgkN = 0; inputN > 0; lgkN++, inputN/=k) ;
    return lgkN;

    //类似方法
//    for(lgkN = 0, t=1; t < N; lgkN++, t+=t) ;
//    return lgKn;
}

int get_half_N_upper_or_down(int inputN, bool upper){
    if(upper)
        return inputN - inputN/2;
    else
        return inputN/2;
}

// 数组参数.
// 顺序搜索
// 保证性能 和 预测性能.
int sequence_search(int a[], int len, int v){
    int i;
    for(i = 0; i <= len; i++){
        if(v == a[i])
            return i;
    }
    return -1;
}

// 二分查找算法
/* 核心:
  1 有序表
  2 每次二分位置 bin_pos = (len + cur)/ 2. (当前位置cur + len 除 2, 就是下次查找位置)
  3 循环终止条件(数组长度len >= cur 当前查找位置)

二分搜索的性能:
    C(N) = C(N/2) + 1 其中  C(1) = 1; 递归方程求解即可得到.
    问题规模是 一百万时, 二分搜索每次事务 最多需要20次查找即可！！
*/
int binary_search(int a[], int len, int v){
    int cur = 0;
    int bin_pos = 0;

    while(len >= cur){

        bin_pos = (len + cur) / 2;

        if(v == a[bin_pos])
            return bin_pos;

        if(v < a[bin_pos])
            len = bin_pos - 1;
        else
            cur = bin_pos + 1;
    }

    return -1;

}

void main(){
    printf("%d \n", get_half_N_upper_or_down(97, true));
    printf("%d \n", get_half_N_upper_or_down(97, false));
}
