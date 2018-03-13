#include "common_data.h"
#include <time.h>

void generate_array_int(int a[], int length){
  int i, j;
  i = 0;
  srand(time(NULL));
  for(i = 0; i < length ; i ++){
    a[i] = rand()%MAX_INT;
  }
  return ;
}


void print_array_int(int a[], int length){
  int i = 0;
  for(i = 0; i < length; i++)
    printf("%d ", a[i]);
  printf("\n");
}
