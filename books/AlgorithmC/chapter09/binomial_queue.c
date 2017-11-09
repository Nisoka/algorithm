#include "binomial_queue.h"

#define BQ_INDEX_SIZE_MAX 1000
bq_link z = NULL;

struct bq_node{
    Item key;
    bq_link l, r;
};

//连接两个2次幂堆
bq_link pair(bq_link p, bq_link q)
{
    if(less(p->key, q->key)){
        p->r = q->l;
        q->l = p;
        return q;
    }else{
        q->r = p->l;
        p->l = q;
        return p;
    }

}

bq_link bq_insert(binomial_queue *bin_q, Item v)
{
    int i;
    bq_link c, t = malloc(sizeof *t);
    c = t;
    c->l = z;
    c->r = z;
    c->key = v;
    //从1节点2次幂堆开始
    for(i = 0; i < BQ_INDEX_SIZE_MAX; i++){
        if(c == z)
            break;
        //如果该位置2次幂堆为空 表示可以进位 退出了.
        if(bin_q->bq[i] == z){
            bin_q->bq[i] = c;
            break;
        }
        //两个2次幂堆相加,此时一定需要进位了8 4 2 1, c 此时需要尝试进位.
        // 原本的位清零=NULL;
        c = pair(c, bin_q->bq[i]);
        bin_q->bq[i] = z;
    }

    return t;
}

bq_link bq_delmax(binomial_queue *bin_q)
{
    int i;
    int max;
    bq_link x;
    Item v;
    bq_link temp[BQ_INDEX_SIZE_MAX];

    for(i = 0, max = -1; i < BQ_INDEX_SIZE_MAX; i++){
        if(bin_q->bq[i] != z){
            if((max == -1) || less(v, bin_q->bq[i]->key)){
                max = i;
                v = bin_q->bq[max]->key;
            }
        }
    }
    x = bin_q->bq[max]->l;
    for(i = max; i < BQ_INDEX_SIZE_MAX; i++)
        temp[i] = z;
    //将bin_q->bq[max]->l 剩下的完全树, 转化为一个新的二项队列.
    for(i = max; i > 0; i--){
        temp[i-1] =x;
        x = x->r;
        temp[i-1]->r = z;
    }
    //删除不用节点
    free(bin_q->bq[max]);
    //max位 2次幂堆 已经转为一个临时 二项队列, 这里去掉.
    bin_q->bq[max] = z;

    bq_join(bin_q->bq, temp);
    return v;

}

void bq_join_kernel(bq_link *a, bq_link *b)
{
    int i;
    bq_link c = z;
    //逐位进行加法.
    for(i = 0; i < BQ_INDEX_SIZE_MAX; i++){
        //判断加法进位条件.
        switch(test(c!=z, b[i]!=z, a[i]!=z)){
        case 2:
            a[i] = b[i];
            break;
        case 3:
            c = pair(a[i], b[i]);
            a[i] = z;
            break;
        case 4:
            a[i] = c;
            c = z;
            break;
        case 5:
            c = pair(c, a[i]);
            a[i] = z;
            break;
        case 6:
        case 7:
            c = pair(c, b[i]);
            break;
        }
    }
}

void bq_join(binomial_queue *a, binomial_queue *b){
    bq_join_kernel(a->bq, b->bq);
}

