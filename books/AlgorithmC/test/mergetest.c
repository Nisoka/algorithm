
#include "../common/item_int.h"

void merge_ab(Item c[], Item a[], N, Item b[], M){
  int i, j, k;
  for(i = 0, j = 0, k = 0; k < M+N; k++){
    if(i == N){
      c[k] = b[j++];
      continue;
    }
    if(j == M){
      c[k] = a[i++];
      continue;
    }

    c[k] = less(a[i], b[j])?a[i++]:b[j++];
  }
}

#define MAX_SIZE 100000
Item aux[MAX_SIZE];
void merge(Item a[], int l, int m, int r){
  int i, j, k;
  // i = l;
  for(i = m+1; i > l; i--)
    aux[i-1] = a[i-1];

  // j = r
  for(j = m; j < r; j++)
    aux[r+m-j] = a[j+1];

  for(k = l; k <= r; k++){
    if(less(aux[j], a[i])){
      a[k] = aux[j--];
    }else{
      a[k] = aux[i++];
    }
  }
}


void merge_sort(Item a[], int l, int r){
  int m = (l+r)/2;
  if(r <= l)
    return ;
  
  merge_sort(a, l, m);
  merge_sort(a, m+1, r);
  merge(a, l, m, r);
}
