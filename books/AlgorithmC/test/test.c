#include "../common/item_int.h"

void sort_select(Item a[], int l, int r]){
  int i, j;
  int minIndex = 0;

  for(i = l; l < r; l++){
    minIndex = i;
    for(j = i+1; j < r; j++){
      if(less(a[j], a[minIndex]))
        minIndex = j;
    }
    a[i] = a[minIndex];
  }
}

void sort_insert(Item a[], int l, int r){
  int i, j;
  Item v;
  //i == l stop;
  for(i = r; i > l; i--){
    if(less(a[i-1], a[i]))
       exch(a[i-1], a[i]);
  }

  for(i = l+1; i < r; i++){
    v = a[i];
    //有观嚓哨 不需要使用 for(j = i; j > l; j--) 多判断一个 j > l 条件
    //less 内部 判断 a < b 小于说明需要exch
    while(less(v, a[j-1])){
      //空位法 留下空位 向后赋值
      a[j] = a[j-1];
      //最终 j-- 后 j就是目标地址
      j--;
    }
    a[j] = v;    
  }
}


void sort_bubble(Item a[], int l, int r){
  int i, j;
  //目标位置 i
  for(i = l; i < r; i++){
    //每次冒泡 从r开始冒泡到目标位置i 
    for( j = r; j > i; j--){
      if(less(a[j], a[j-1]))
        exch(a[j-1], a[j]);
    }
  }
}



void sort_shell(Item a[], int l, int r){
  int i, j;
  int h;
  Item v;
  //h 十分之一 的总长度 作为最大插入间隔 ， 如此计算 最终h/=3 最后的h就是1
  for(h = 1; h < (r-l)/9; h = 3*h+1) ;
  
  for(; h > 0; h/=3){
    
    for(i = l+h; i < r; i++){
      v = a[i];
      j = i;
      while (j >= i+h && less(v, a[j])) {
        a[j] = a[j-h];
        //j 就是目标空位
        j-=h;
      }
      a[j] = v;
    }
  }
}


/*
quick sort
*/

int partition_quicksort(Item a[], int l, int r){
  int i = l-1;
  int j = r;
  Item v = a[r];
  while (1) {
    //i 大于v的 元素index
    while(less(a[++i], v)) ;
    while(less(v, a[--j])) 
      if(j == l)                               
        break;
    
    //此时 已经将a 关于a[r]划分开两半，
    //此时a[i] 是less(a[i], v) false 条件 在跳出while后exch。
    if(i >= j)
      break;

    exch(a[i], a[j]);
  }
  exch(a[i], a[r]);
  return i;
}


void quick_sort(Item a[], int l, int r){
  int i;
  //分治快排 完成
  if(r <= l)
    return ;
  i = partition(a, l,  r);
  quick_sort(a, l, i-1);
  quick_sort(a, i+1, r);
}


void _quick_sort_add_insert(Item a[], int l, int r){
  int i;
  if(r -l <= M)
    return ;
  
  i = partition(a, l, r);
  quick_sort_add_insert(a, l, i-1);
  quick_sort_add_insert(a, i+1, r);
}

void quick_sort_add_insert(Item a[], int l, int r){
  _quick_sort_add_insert(a, l, r);
  insert_sort(a, l, r);
}
