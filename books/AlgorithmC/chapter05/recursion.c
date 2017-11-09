#include <stdlib.h>
#include <stdio.h>
/*
//1 递归方程 与 递归程序之间的关系 递归程序实例
//2 分治法的基本递归模式
//3 动态规划的实现递归程序的一般方法. 它能为一大类问题提供精致高效的解决方法.
//4 研究树及其数学性质, 还有与之相关的算法 树遍历
//5 处理图的相关方法. 并特别关注一种基本递归程序 -- 深度优先搜索, 许多图处理算法的基础.
// 递归公式也为我们研究其他非递归的高效算法提供了框架
*/

int factorial(int N){
  if(N == 0)
    return 1;
  return N*factorial(N-1);
}

// 阶乘的非递归方法, 通过递归公式很容易实现.
int factorial_not_recursion(int N){
    int ret = 1;
    for(;N > 0; N--){
        ret *=N;
    }
    return ret;
}


//有问题的递归调用, 不能用归纳法证明该程序能够终止. 因为并不是每一次调用 参数都变小
int puzzle(int N){
    if(N == 1)
        return 1;
    if(N%2 == 0){
        return puzzle(N/2);
    }else{
        return puzzle(3*N + 1);
    }

}

//欧几里得算法 2000年历史. m n(m > n)两个数的最大公因数等于 n m%n 的最大公因数.
//当 m%n == 0 时, 说明 m == n*k, n就是最大公因数.
// 结束条件 m n 当n 为0 m为最大公因数
// 归纳证明 每次递归调用 m n 都会进入下一次 n m%n 的判断是否已经达到最大公因数
//      n m%n 是会逐渐减小的参数。
int gcd(int m, int n){
  if(n == 0)
    return m;
  
  return gcd(n, m%n);
}


/*
//原则上 我们可以用等价的递归程序 替代 for, 并且递归尝尝是更为自然的描述方式.
// 但是递归有一个固有问题, 就是 递归调用 是嵌套调用, 是需要有额外开销记录调用的,
// 而一般这个额外开销是通过 下堆栈(函数堆栈) 实现的, 因此深度过大时 堆栈溢出问题.
*/
//前缀 求值 表达式字符串.
char *a;
//字符串上 递归游标.
int index;

//前缀表达式求值 
int prefix_eval(){
  int x = 0;
  //空格 继续向下判断
  while(a[index] == ' ')
    index++;
  //＋需要下面两个操作数 递归获得操作数，如果下面依旧是操作符 则还会递归进行
  if(a[index] == '+'){
    index++;
    return eval() + eval();
  }
  if(a[index] == '*'){
    index++;
    return eval() * eval();
  }
  //数字的构建
  x = 0;
  if(a[index] >= '0' && a[index]<='9'){
    x = 10*x + (a[index++]-'0');
  }
  return x;
}


#include "../common/link_base.h"
int count(link x){
    if(x == NULL)
        return 0;
    return 1 + count(x->next);
}

void traverse(link h, void (*visit)(link)){
    if(h ==NULL)
        return  ;
    (*visit)(h);
    traverse(h->next, visit);
}

void traverseR(link h, void (*visit)(link)){
    if(h == NULL)
        return ;
    traverseR(h, visit);
    (*visit)(h);
}

link delete_link(link h, Item v){
    if(h == NULL)
        return h;
    if(eq(h->item, v)){
        link t = h;
        h = h->next;
        free(t);
        return h;
    }
    h->next = delete_link(h->next, v);
    return h;
}


// 递归实现的本质 是使用下堆栈数据结构 来实现 函数的递归调用.
// 递归的深度 就是 函数在计算过程中递归调用的最大次数.
// 带有指针的节点所构建的链表 这种数据结构本质上也是递归的, 定义也是递归性质.


/*
//递归函数 两个根本点 或者说 必须有效的证明函数可行.
//1 归纳基础 必须被解决 -- 结束条件明确被处理
//2 归纳证明 每一次递归调用 必须向着结束条件而去.

// 总是可以使用 非递归程序 完成递归要完成的操作, 同样也可以使用递归来完成循环要完成的操作.
// 使用递归 是因为 递归可以更简洁、更紧凑、清晰的表达复杂的算法, 且不牺牲效率.
*/


// 5.2 5.3 分析讨论两类 基本计算泛型算法.
// 5.4 5.7 作为很多算法的基础的数据结构.

/*
//5.2 分治法范型.
// 范型--- 模式, 求解思路, 思考方式.
// 分治法的核心是 一个问题 能够被递归的划分为两个(或者多个)相同的小问题.
*/

/*

  5.3 动态规划
