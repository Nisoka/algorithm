#include "heap_index.h"
#include "time.h"

#define N 20
int a[N];

int Priority(int i, int j) {
  return a[i] < a[j];
}  // 定义优先级函数




int main(){
  srand(time(NULL));
  PQinit(N);
  int i;
  printf("Array:\n");

  for(i = 0; i < N; ++i){  // 生成100以内的随机数组并输出
    a[i] = rand() % 100;
    PQinsert(i);   // 将生成的随机数的下标插入到索引堆
    printf("%d ", a[i]);
  }
  printf("\nhead_sorted: \n ");

  while (!PQempty())  // 将元素按照从小到大的顺序输出
    printf("%d ", a[PQdelmax()]);
  printf("\n");
  return 0;
}
