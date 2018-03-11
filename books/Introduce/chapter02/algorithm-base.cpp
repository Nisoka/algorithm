#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;


#define MAX_INT 200
void generate_date_int(int a[], int length){
  int i, j;
  i = 0;
  srand(time(NULL));
  for(i = 0; i < length ; i ++){
    a[i] = rand()%MAX_INT;
  }
  return ;
}






void print_date_array(int a[], int length){
  int i = 0;
  for(i = 0; i < length; i++)
    printf("%d ", a[i]);
  printf("\n");
}


void insertion_sort(int a[], int length){
  int i, j, key;
  i = 1;
  print_date_array(a, length);
  
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
  print_date_array(a, length);
}

int main(int argc, char* argv[]){

  int a[100] = {};
  int length = 10;
  generate_date_int(a, length);
  insertion_sort(a, length);
}


