#include "common_int.h"

int random_int(){
   return rand()%MAX_INT - MAX_INT/2;
}

namespace nan_int {




void generate_array_int_for_debug(int a[], int length){
  int i;
  i = 0;
  for(i = 0; i < length ; i ++){
    a[i] = i;
  }
  print_array_int(a, length);
  return ;
}
void generate_array_int(int a[], int length){
  int i;
  i = 0;
  srand(time(nullptr));
  for(i = 0; i < length ; i ++){
    a[i] = random_int();
  }
  print_array_int(a, length);
  return ;
}

void generate_vec_int(vector<int> *a, int length){
    int i = 0;
    srand(int(time(nullptr)));
    a->resize(length);
    vector<int>::iterator iter = a->begin(), end = a->end();

    while(iter != end){
        i = random_int();
        *iter = i;
        iter++;
    }


    print_vec_int(*a);

}


void print_array_int(int a[], int length){
  int i = 0;
  for(i = 0; i < length; i++)
    printf("%d ", a[i]);
  printf("\n");
}


void print_vec_int(vector<int> a){
    vector<int>::iterator iter = a.begin(), end = a.end();
    printf("iter the vector : ");
    while(iter != end){
        printf("%d ", *iter);
        iter++;
    }
    printf("\n");
}

}
