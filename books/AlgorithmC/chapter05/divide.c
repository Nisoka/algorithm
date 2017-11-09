#include <stdlib.h>
#include <stdio.h>

#include "../common/item_int.h"

// 分治算法 对应的是 数组的二进制表示 中 0 的个数.
// 因为分治算法 就是 将问题1/2, 然后在1/2求解的.
// 二进制的进一位方式 是递归的需要前一位进一. 最终递归到最末位. 0 1 0 1.

/*
 0  1  2   3  4  5
 l     m   m+1   r
m = (0 + 5)/2 == 2;
 该分治法 求解证明:
 1 明确求解了 当部分只有1时的数值
 2 每次递归都减少规模 求解问题的一小部分.
 分治法将问题 分为小部分, 并且在递归下 每个小部分又分为更小部分, 然后最终通过最小问题的解决将整个问题解决..
*/
Item max(Item a[], int l, int r){
    int m = 0;
    Item u, v;
    m = (l + r)/2;

    if(l == r)
        return a[l];

    u = max(a, l, m);
    v = max(a, m+1, r);
    if(u > v)
        return u;
    else
        return v;
}

void test_max_divide(int maxN){
    int i = 0;
    Item *a = malloc(maxN * sizeof(Item));
    for(i = 0; i < maxN; i++){
        a[i] = rand()%20;
    }

    printf("%d ", max(a, 0, maxN-1));
}

//将n个盘子 从a 移动到 c.
/*
核心思想是
 1  前面n-1个   从 a -> b
 2  最后n一个   从 a -> c
 3  前面n-1个   从 b -> c
 步骤1 实现思想核心是: 前 n-1个 怎么从a -> b
     1  前面n-2个    从 a -> c
     2  最后n-1一个   从 a -> b
     3  前面n-2个    从 c -> b
         步骤1 实现
                 步骤1 实现
如此递归, 最后到达
     1  前面1 一个    从 a -> c
     2  最后2 一个   从 a -> b
     3  前面1 一个    从 c -> b
这样就可以得到移动了.

递归的核心是:
    递归问题, 循环由子问题c构成父问题f, 最终有一个最小可处理问题e.
    这样
                e
            c
        f       e
            c   e

                e
    在求解f 时 需要求解c, 求解c 又需要求解e.
    这样递归到e时, 处理e 返回的结果能够处理c, 然后最后处理f.
*/

//

void hanoi_move(int n, char src, char tmp, char target){
    if(n == 0){
        return ;
    }else{
        hanoi_move(n-1, src, target, tmp);
        printf("%d: %c -> %c\n",n, src, target);
        hanoi_move(n-1, tmp, src, target);
    }
}

void mark(int m, int h){
    printf("%d:", m);
    while(h--){
        printf("-");
    }
    printf("\n");
}

void rule(int l, int r, int h){
    int m = (l+r)/2;
    if(l == m)
        return ;
    if(h > 0){
        rule(l, m, h-1);
        mark(m, h);
        rule(m, r, h-1);
    }
}

void rule_down2up(int l, int r, int h){

}

int main(int argc, char* argv[]){
//    hanoi_move(atoi(argv[1]), 'a', 'b', 'c');
    rule(0, 8, 4);
}
