#include "common/common_int.h"
using namespace nan_int;
void merge_array(int a[], int aux[], int l, int m, int r){
    int i, j, k;
    i = 0;
    j = 0;

    // 0, 1, 2 .... 9
    //l -start_pos(0)
    //r -end_pos(9)
    //m -middle_pos(4)
    int len1 = m - l + 1;
    int len2 = r - (m+1) +1;

    for(i = 0; i < len1+len2+2; i++){
        aux[i] = 0;
    }

    i = 0;
    while(i < len1){
        aux[i] = a[l+i];
        i++;
    }
    //i == len1
    aux[i] = SENTINEL_INT;
    //i == len1 + 1
    i++;



    while(j < len2){
        aux[i+ j] = a[m+1+ j];
        j++;
    }

    aux[i+j] = SENTINEL_INT;

    i = 0;
    // 正常0起始
    j = len1+1;
    // 注意哨兵位置.为 aux[len1], 所以 辅助数组的 归并第二部分从 len1+1 为0起始

    k = l;
    while(k < r+1){
        printf("aux i, j %d, %d \n", aux[i], aux[j]);
        if(aux[i] < aux[j]){
            a[k++] = aux[i++];
        }else{
            a[k++] = aux[j++];
        }
    }
}


void merge_sort(int a[], int aux[], int l, int r){
    int m = (l + r)/2;
    if(l >= r)
        return ;

    // left half  l=0 --> m (len = m+1 -l)
    merge_sort(a, aux, l, m);
    // right half m+1=0 --> r (len = r-m)
    merge_sort(a, aux, m+1, r);

    merge_array(a, aux, l, m, r);

}





int merge_sort_main(int argc, char* argv[]){
    int len = 0;
    if(argc == 2){
        len = atoi(argv[1]);
    }else{
        len = 20;
    }


    int *a = (int *)malloc((unsigned long)len*sizeof(int));
    int *aux = (int *)malloc((unsigned long)(len+4)*sizeof(int));


    generate_array_int(a, len);

    print_array_int(a, len);

    merge_sort(a, aux, 0, len-1);
    // 不好解决时候, 最好各自功能进行实现.
    // merge_array(a, aux, 0, (len-1)/2, len-1);
    print_array_int(a, len);


    free(a);
    free(aux);
}


