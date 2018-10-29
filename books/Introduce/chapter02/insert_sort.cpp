#include <stdio.h>
#include <stdlib.h>
#include "common/common_int.h"

using namespace std;
using namespace nan_int;
void insertion_sort(int a[], int length){
    int i, j, key;
    i = 1;
    print_array_int(a, length);

//    while(i < length){
//        key = a[i];
//        j = i - 1;
//        while(j >= 0 && key < a[j]){
//            a[j+1] = a[j];
//            j--;
//        }
//        a[++j] = key;
//        i++;
//    }

    while(i < length){
        key = a[i];
        j = i - 1;
        while(j >= 0 &&  a[j] > key){
            //向后移动一位.
            a[j+1] = a[j];
            j--;
        }
        a[++j] = key;
        i++;
    }


    print_array_int(a, length);
}

int insert_sort_main(){

    int a[100] = {};
    int length = 10;
    generate_array_int(a, length);
    insertion_sort(a, length);
    return 0;
}


