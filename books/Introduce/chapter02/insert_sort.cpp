#include <stdio.h>
#include <stdlib.h>
#include "../common/common_data.h"

using namespace std;

void insertion_sort(int a[], int length){
  int i, j, key;
  i = 1;
  print_array_int(a, length);
  
  while(i < length){
    key = a[i];
    j = i - 1;
    while(j >= 0 && key < a[j]){
      a[j+1] = a[j];
      j--;
    }
    a[++j] = key;
    i++;    
  }
  print_array_int(a, length);
}

int main(int argc, char* argv[]){

  int a[100] = {};
  int length = 10;
  generate_array_int(a, length);
  insertion_sort(a, length);
}


