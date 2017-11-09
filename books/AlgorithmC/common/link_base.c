#include "link_base.h"



link link_malloc()
{
    return (link)malloc(sizeof(struct node));
}

void link_print(const link s){
    link t = s;
    while(t != NULL){
        print_item(t->item);
        t = t->next;
    }
    nprint_n;
}

//函数定义实现时, 不能使用定义默认参数, 只有在声明时可以使用默认参数.
link link_create(int length, int random){
    int i;
    link s = link_malloc();
    link t = s;
//    printf("%s-%s: \n", __FILE__, __FUNCTION__);
    nlog(__FUNCTION__, "start");
    s->item = 1;

    if(random == 0){
        for(i = 2; i <= length; i++){
            t->next = link_malloc();
            t = t->next;
            t->item = i;
            t->next = NULL;
        }
    }else {
        for(i = 2; i <= length; i++){
            t->next = link_malloc();
            t = t->next;
            t->item = rand()%1000;
            t->next = NULL;
        }
    }
    print_link(s);
    return s;
}


//link a 成为参数, 虽然是一个新的link对象,
//但是link本身是个指针对象,内部值是一个地址, 需要的是那个地址
void link_free(link a)
{
    free(a);
}

link new_link_node(Item item)
{
    link t = malloc(sizeof(struct node));
    t->item = item;
    t->next = NULL;
    return t;
}
