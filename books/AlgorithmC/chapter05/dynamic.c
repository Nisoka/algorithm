#include <stdlib.h>
#include <stdio.h>

/*
  5.3 动态规划
1 自底向上动态规划 技术
  1 预先计算小问题的解。
  2 对于大问题通过利用前面计算出来的值,保存下来, 用来计算当前的值.
  使用数组保存已计算数据的技术 给了我们一个 获取任何递归关系数值解的快速方法
  这是一个设计算法的技术, 已经广泛引用于很多算法, 我们必须注意简单技巧, 将算法从指数级运行时间向线性运行时间改进.
*/
/*
2 自顶向下动态规划 技术
  我们实现递归程序, 在递归程序计算过程中动态的保存它计算的每个子问题的值, 在计算新值时, 递归程序检查所需要的以前值, 是否已经有保存. 进而省去递归过程的技术.
  消除了所有重复计算!!!!!
  自底向上 和 自顶向下的区别在于:
  自底向上 预先先把所需要的前期数据都计算出来保存到起来, 从底向上进行递归计算？
  自顶向下 在求解过程中遇到了再计算保存小问题解值, 并自顶向下递归过程中检查其 递归子问题是否已经有了答案,进而减少很多计算. 
  相对来说 自顶向下技术 是懒惰算法，自底向上技术是积极算法，在不通情况下，各有利弊。
*/  



/*
 时间复杂度是 1.618^N; 指数级时间复杂度.
    N 次递归深度.
    每次递归可分支两个 但是并不是完全等分 所以是 1.618.
    使用数组保存前N个斐波那契数, 这个方法将使用线性时间 获得结果.
*/
int Fibona(int n){
    if(n < 1)
        return 0;
    if(n == 1)
        return 1;

    return Fibona(n-1) + Fibona(n-2);
}

#define DYNAMIC_MAX 100
#define DYNAMIC_UNKNOWN 321321
int known[DYNAMIC_MAX];

int Fibona_dynamic(int n){
  int t;
  if(known[n]!=DYNAMIC_UNKNOWN)
    return known[n];
  if(n == 0)
    return 0;
  if(n == 1)
    return 1;
  if(n > 1)
    t = Fibona_dynamic(n - 1) + Fibona_dynamic(n - 2);
  return known[n] = t;
}

void test_dynamic_fibona(int n){
  int i = 0;
  for(i = 0; i < DYNAMIC_MAX; i++){
    known[i] = DYNAMIC_UNKNOWN;
  }
  for(i = 0; i < 20; i ++)
    printf("%d ", Fibona_dynamic(i));
}


//背包算法
typedef struct{
  int size;
  int val;
}Item;
  
#define N 10
Item item[N];

int knap(int cap){
  int i, space, max, t;
  for(i = 0, max = 0; i < N; i++){
    if((space = cap - item[i].size) >= 0)
      if((t = knap(space) + item[i].val) > max)
	max = t;
  }
  return max;
}
#define SIZE_MAX 100
#define UNKNOWN 321321
int maxKnown[SIZE_MAX];

int knap_dynamic(int cap){
  int i, space, max, maxi, t;

  if(maxKnown[cap] != UNKNOWN){
    return maxKnown[cap];
  }
  for(i = 0, max = 0; i < N; i++){
    if( (space = cap - item[i].size) >= 0 ){
      if( (t = knap_dynamic(space) + item[i].val) > max){
        max = t;
        maxi = i;
      }
    }
  }
  maxKnown[cap] = max;
  return max;
}



int main(int argc, char *argv[]){
    int p1 = atoi(argv[1]);
    test_dynamic_fibona(p1);
}

