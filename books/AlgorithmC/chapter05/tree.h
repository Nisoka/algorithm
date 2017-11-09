#ifndef TREE_H
#define TREE_H
/*
5.4 树 定义
    什么是树, 有那些树, 树是递归定义的.
5.5 树的数学性质
    什么树有多少个节点、多少个边.
5.6 树的遍历
*/
/*
二叉树的构造和其他算法处理 的基础 --- 树遍历处理.
  给出一个指向树的指针, 按某个顺序系统的访问树种的每个节点.
  因为二叉树本身就是 递归定义的, 所以我们可以容易的使用递归 程序实现遍历.
*/

// 树的核心是 树的递归结构,
//      树 是一个链接 -- 指向节点的链接, 该节点是包含数据项和其子树的链接.
//                          最终子树是空, 该节点为叶节点 在递归中返回的终结节点.
// 树就是递归 递归就是树.

typedef int Item;
typedef struct node_tree* link;

struct node_tree{
    Item item;
    link l;
    link r;
};

// 实现见 #include "../chapter04/stack.h"
void stack_init(int);
int  stack_empty();
void stack_push(link);
link stack_pop();

void easy_visit(link t);

#endif // TREE_H
