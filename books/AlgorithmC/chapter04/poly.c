#include "poly.h"

struct poly{
    int N;      //最高次项 + 偏移项 总数.
    int *a;     //各项参数
};

//抽象数据类型 + 数组.
//怎么描述 一个 polynomial 系数 + 度.

Poly poly_term(int coeff, int exp)
{
    int i = 0;
    Poly p = malloc(sizeof(struct Poly));
    p->a = malloc((exp+1)*sizeof(int));
    p->N = exp+1;       //从0 开始 到
    p->a[exp] = coeff;  //最低次 偏移值.
    for(i = 0; i < exp; i++)
        p->a[i] = 0;
    return p;
}


Poly poly_add(Poly p, Poly q){
    int i;
    Poly t;
    if(p->N < q->N){
        t = p;
        p = q;
        q = t;
    }

    for(i = 0; i < p->N; i++){
        p->a[i] += q->a[i];
    }
    return p;
}

Poly poly_mul(Poly p, Poly q){
    int i, j;
    Poly t = poly_term(0, (p->N - 1) + (q->N - 1));
    for(i = 0; i < p->N; i++){
        for(j = 0; j < q->N; j++){
            t->a[i+j] += p->a[i]*q->a[j];
        }
    }

    return t;
}

//x^2 + 3x + 3 =
//2     1    0
//i = 2, a[2] = 1
//0x + 1        t = 1
//i = 1, a[1] = 3
//1x + 3        t = 1x + 3
//i = 0, a[0] = 3
//x^2 + 3x + 3
Poly poly_eval(Poly p, float x){
    int i = 0;
    double t = 0.0;
    for(i = p->N-1; i >= 0; i--){
        t = t*x + p->a[i];
    }
    return t;
}
