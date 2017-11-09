#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "blibs/number_float.h"
#include "blibs/struct_point.h"


/*
  3.2 数组
    数组常用的使用方式:
        index       代表对象
        a[index]    代表对象属性.

        C语言中 数组a a 直接就是一个指针
            *a  <==> a[0]    *(a+i) <==> a[i]

    用对象做索引 索引就是对象，而数组内容实际上始标记。

    或者说是 使用数据计算得到数组的索引值，实际上 使用计算出的值进行访问N大小的数组时，相对于link链表来说，用计算代替了遍历，收获巨大效益。
    最重要的应用地点就是 hash函数 直接计算关键字的数组索引。

    这种范型叫: 关键字索引
    eg 关键字索引算法、hash表
        
*/

/* 埃拉托色尼筛选素数法
 基本抽象操作:
    证明一个数是素数 - 该数不是小于其的所有素数的倍数,则认为该数是素数.
    或者理解为 所有数(除去1)的倍数都不是素数, 只要找到所有非素数即可.
 素数(没有非1因子)prime_number = 1;

 数据结构 - 数组:
    index 代表对象, 1 2 3...
        特点利用对象直接相乘即可得到是不是一个素数
    a[index] 代表素数非素数标记.
*/
void print_prime_number(int n_cnt){
    int i, j;
    int *a = NULL;
    a = malloc(n_cnt*sizeof(int));
    if(a == NULL){
        printf("Malloc failed return !\n");
        return ;
    }

    //初始化 所有数都使素数
    for(i = 0; i < n_cnt; i++)
        a[i] = 1;

    /* 从i 开始 所有素数的倍数都不是素数.
      为什么 j 从i 开始
      一般情况下无序配对 j 就从 i 开始, 但这里j 从i 开始并不是这个原因:
      j从i开始的原因是i以前的数已经判断了, i 以前的数x 如果x为素数, 那么a[x*i]肯定已经设置为素数.
      所有数的倍数都不是素数.
      而又有 非素数都是某个素数的倍数, 所以只要考虑素数的倍数即可, 这样就减少循环次数.
    */
    for(i = 2; i < n_cnt; i++){
        //只需 考虑所有 素数的倍数即可, 非素数都是素数的倍数.在之前已经判断过了
        if(a[i]){
            //标记所有证明 的 非素数 i*j < n_cnt 
            for(j = i; i*j < n_cnt; j++)
                a[i*j] = 0;
        }
    }

    for(i = 2; i < n_cnt; i++){
        if(a[i])
            printf("%4d ", i);
    }
    printf("\n");

    free(a);
}


//binary 0 1 随机数.
bool random_value_greater_than_max_half(){
    return rand() < RAND_MAX/2;
}

/* 二元分布 概率
 数据结构 - 数组
 index 代表 32次正面的cnt 可能的对象有 0 - 32.
 oneshot[index] 代表那么多次测试下 发生index次正面的次数.
*/
void coin_distribute(int possible_cnt, int test_times){
    int i, j, cnt;
    int *possible_array;
    possible_array = (int *)malloc(possible_cnt * sizeof(int));

    for(i = 0; i < possible_cnt; i++)
        possible_array[i] = 0;

    //进行 test_times x 32遍coin统计.
    for(i = 0; i < test_times; i++){
        //每次 32遍coin正反面统计.
        for(cnt = 0, j = 0; j < possible_cnt; j++){
            if(random_value_greater_than_max_half())
                cnt++;
        }
        //cnt 就是目标对象，出现正面的次数，对次数进行统计纪录
        possible_array[cnt]++;
    }

    for(i = 0; i < possible_cnt; i++){
        printf("%d ", i);
        for(j = 0; j < possible_array[i]; j++)
            printf("*");
        printf("\n");
    }

    free(possible_array);
}

/* 上面两个 求素数 和 求伯努利分布的函数
    都利用数组作为数据结构 保存对应数据对象的 状态或者信息,
    ××用索引直接代表对应对象. 数组对很多用int对象的用法.
    从数据 计算 索引值,从某种意义上 我们用计算出的值访问大小为N的数组时, 只用一个操作数就考虑了N种可能.
    当我们实现这一点时, 所获得的效益是巨大的.
    贯穿全书都会遇到以这种方式使用数组的算法.
    数据对象是用索引值代表.
*/




//单位正方形(边长为1)内,两点间距离 < max_distance
void distance_shorter(int n_cnt, float max_distance){
    int i, j, cnt = 0;
    point *a = malloc(n_cnt*sizeof(point));


    for(i = 0; i < n_cnt; i++){
      point_malloc(&a[i]);
      point_initial(a[i], 1.0);
    }

    for(i = 0; i < n_cnt; i++){
        //j 从i+1 起始,
        //最基本的算法就是很多时候 是从 i开始, 因为 小于i的 都在之前被判断过了.
        //无序配对 j 从 i 开始.
        for(j = i + 1; j < n_cnt; j++){
          float temp = distance(a[i], a[j]);
          if(temp < max_distance){
            printf("distance is %f \n", temp);
            cnt++;
          }
        }
    }

    printf("%d edges shorter than %f\n", cnt, max_distance);
}


int main(int argc, char *argv[]){
  //int paramter = atoi(argv[1]);
  //print_prime_number(paramter);
    int par1 = atoi(argv[1]);
    int par2 = atoi(argv[2]);
    distance_shorter(par1, par2);
}
