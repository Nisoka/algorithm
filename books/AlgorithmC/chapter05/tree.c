#include <stdlib.h>
#include <stdio.h>

#include "tree.h"




typedef void (*func_type)(link);
//递归方式前序遍历树h
void traverse_pre(link h, void (*visit)(link)){
    if(h == NULL)
        return ;
    (*visit)(h);
    traverse_pre(h->l, visit);
    traverse_pre(h->r, visit);
}

//树的入栈就是这么简单 将一棵树的指针入栈即可, 因为树是递归结构,
//将树的指针入栈 实际上已经可以通过树的递归结构性质认为整棵树都可以在栈中了.
//原因如下:
int max = 100;
void traverse_pre_in_stack(link h, void (*visit)(link)){
    stack_init(max);
    stack_push(h);  //树入栈
    while(!stack_empty()){
        //树前序遍历
        h = stack_pop();
        visit(h);
        //注意 使用栈实现树遍历 入栈顺序要与遍历顺序相反
        if(h->r != NULL)
            stack_push(h->r);
        if(h->l != NULL)
            stack_push(h->l);
    }
}



/*
//5.7递归二叉树算法














*/
//直接根据树的定义  递归的有两棵子树.
//
int count(link h){
    if(h == NULL)
        return 0;
    //左树节点数 右树节点数 本节点
    return count(h->l) + count(h->r) + 1;
}

int height(link h){
    int u, v;
    //非节点
    if(h == NULL)
        return -1;
    //递归过程
    u = height(h->l);
    v = height(h->r);

    //递归处理
    if(u > v)
        return u+1;
    else
        return v+1;
}


void print_tree_node(char c, int h){
    int i;
    printf("%c:", c);
    for(i = 0; i < h; i++){
        printf(" ");
    }
    printf("*\n");
}

void plot_tree(link h, int heigh){
    if(h == NULL)
        return ;
    if(h->l != NULL) plot_tree(h->l, heigh+1);
    print_tree_node(h->item, heigh);
    if(h->r != NULL) plot_tree(h->r, heigh+1);
}


link new_tree_link(Item item, link l, link r){
    link x = malloc(sizeof(struct node_tree));
    x->l = l;
    x->r = r;
    x->item = item;
    return x;
}

link max(Item a[], int l, int r){
    int m = (l + r)/2;
    Item u, v;
    link x = new_tree_link(a[m], NULL, NULL);
    //一个分治在达到叶节点时才第一次返回. 不然一直递归到最小问题.
    if(l == r)
        return x;

    //分治递归构建联赛
    x->l = max(a, l, m);
    x->r = max(a, m+1, r);

    u = x->l->item;
    v = x->r->item;

    x->item = u > v? u : v;
    return x;
}


typedef struct Tnode* Tlink;

struct Tnode{
    char token;
    Tlink l;
    Tlink r;
};


Tlink new_Tnode_link(char token, Tlink l, Tlink r){
    Tlink x = malloc(sizeof(struct Tnode));
    x->token = token;
    x->l = l;
    x->r = r;
}

char *a;
int i;
//操作符 需要左子节点 和 右子节点 做操作数.
//如果子几点还是操作符, 那么依旧递归需要子节点, 直到叶节点 必然是操作数.
Tlink parse_pre_expression(){
    if(a[i] == '\0')
        return NULL;
    Tlink x = new_Tnode_link(a[i++], NULL, NULL);
    // 如果是操作符
    if(a[i] == '*' || a[i] == '+'){
        x->l = parse_pre_expression();
        x->r = parse_pre_expression();
    }
    return x;
}

void easy_visit(link t)
{
    printf("%d ", t->item);
}
