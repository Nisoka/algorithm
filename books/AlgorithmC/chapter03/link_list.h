#ifndef LINK_LIST_H
#define LINK_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// 必须清楚 一个数据结构 对于算法处理数据的效率有什么影响.
// 或者说 一个问题 主要进行的核心操作是什么, 进而要怎么样的数据结构才能让需求更高效
// 约瑟夫问题 就是一个频繁删除元素的问题, 使用数组 代价昂贵
// 求素数问题 是要快速访问某个数, 访问是算法要求.
typedef int Item;
typedef struct node* link;
#endif // LINK_LIST_H
