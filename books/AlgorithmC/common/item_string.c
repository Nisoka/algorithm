#include "item_string.h"

static char buf[100000];
static int cnt = 0;

#ifdef ABSTRACT_POINTER_SORT
Item item_rand(){
    printf("item string did not support item_rand() \n");
    return NULL;
}

//typedef char* Item
int  item_scan(Item *x){
    int t;
    *x = &buf[cnt];     //字符地址, 字符地址即可以是 0 字符指针 1字符地址 2 字符数组名 3 字符串对象
    t = scanf("%s", *x);
    cnt += strlen(*x) + 1;  //字符串长度 = 字符+\0;
}

void item_show(Item x){
    printf("%s ", x);
}

int compare(void *i, void *j)
{
    return strcmp(*(Item *)i, *(Item *)j);
}

#else


#endif


