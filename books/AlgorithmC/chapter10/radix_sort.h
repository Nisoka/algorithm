#ifndef RADIX_SORT_H
#define RADIX_SORT_H

#include "../common/sort.h"
#include "key_control_byte.h"

/*
    6 - 9 章 排序应用的问题 使用的排序顺序的关键字 都是简单的.
都是比较两个记录的关键字、交换两个记录, 这些基本操作作为排序方法的抽象接口.
    但是实际问题中 定义文件中记录顺序的关键字可以是很复杂的. 所以排序关键字就需要另一种抽象方法.
通常不需要一次进行完整关键字比较, 例如 电话本中查找某个人的电话, 通常检查名字的头几个字母就查找到了.

排序算法中 实现这样的效果, 就是讲关键字分成小部分.
    我们把关键字比较的抽象操作 变成 把关键字分解成一些列定长大小的块
    -- 例如 关键字是4字节的字, 分解为4个字节.
            二进制数         分解为一系列的位.
            字符串           分解为一系列的字符.
            十进制数         分解我一系列的数字。
    这样每次对关键字的一部分进行比较的方法 --- 基数排序.

    基数排序算法 是 把关键字看作以R为基数的数制系统所表示的数字，对于不同的R值, 算法处理这些数字的独立位.
        R为基, 就相当于 考虑每一小部分 所有可能值. 就是基
        eg 整数来说, 一般取 R 为2的n次幂, 因为整数在计算机中是2进制表示, 这样获取部分进行比较方便.
            字符串来说 就使用R = 128 256等 对于全部小写
    这里主要考虑 整数、字符串类型的关键字



*/

void binary_quick_sort(int a[], int l, int r);

#endif // RADIX_SORT_H
