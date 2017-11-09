#include <stdio.h>
#include "string_data.h"

#define N 10000

/*
 *  数组名 既能用于数组索引访问数据, 又能作为指针访问数据.
 对应的 指针   不仅能作为指针访问数据, 也能作为数组索引访问数据.
 数组名 被实现为指针, 指针可以通过 +n 来快速访问任意位置数据.
*/

// 数组做参数, 并不会考虑数组的长度, 只会通过数组名作为指针, 所以写不写数组长度没有区别,没人关心.
int my_str_len(char a[]){
    int i = 0;
    for(i = 0; a[i]!=0; i++) ;
    return i;
}

void my_str_cpy(char a[], char b[]){
    int i = 0;
    // (a[i] = b[i])!=0; C语法 赋值后返回赋值结果.
    for(i = 0; (a[i] = b[i])!=0; i++) ;
}

int my_str_cmp(char a[], char b[]){
    int i = 0;
    for(i = 0; a[i] == b[i]; i++){
        //结束
        if(a[i] == 0)
            return 0;
    }
    return a[i] - b[i];
}

int my_str_ncmp(char a[], char b[]){
    int i = 0;
    for(i = 0; a[i] == b[i]; i++){
        //结束
        if(a[i] == 0)
            return 0;
        if(b[i] == 0)
            return 0;
    }
    return a[i] - b[i];
}


void my_str_cat(char a[], char b[]){
    my_str_cpy(a+strlen(a), b);
}



/// pointer version
int my_str_len_pointer(char a[]){
    char *b;
    b = a;
    // * ++ 谁的操作权限更高? ++. 但是还是会先返回当前b, 执行过后 返回后b 再++.结果b永远多出一位.
    while(*b++) ;
    return b-a-1;
}

void my_str_cpy_pointer(char a[], char b[]){
    // 赋值后会返回赋值结果, 当赋值是0, 赋值后结束.
    while(*a++ = *b++) ;
}


int my_str_cmp_pointer(char a[], char b[]){
    while(*a++ == *b++){
        if(*(a-1) == 0)
            return 0;
    }
    return *(a-1) - *(b-1);
}



void find_pattern_in(char a[], char p[]){
    int i, j;
    for(i = 0; a[i] != 0; i++){     //如果判断条件改为 使用strlen(a) 则每次判断都要执行一遍 时间复杂度就变为 n^2了.
        for(j = 0; p[j]!=0; j++){
            if(a[i+j] != p[j])
                break;
        }
        //查找到字符串结束符, 说明匹配成功
        if(p[j] == 0)
            printf("postion: %d \n", i);
    }
}

int main(int argc, char *argv[]){
    int i , j, t;
    char a[N];
    char * p = argv[1];
    for(i = 0; i < N-1; a[i] = t, i++){
        if((t = getchar()) == EOF)  //EOF(windows ctrl+z  linux ctrl+D)
            break;
    }
    a[i] = 0;
    printf("Input over!\n");
    find_pattern_in(a, p);

    return 0;
}
