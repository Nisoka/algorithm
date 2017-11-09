#include "item_int.h"


Item item_rand()
{
    Item v = rand()%1000;
    return v;
}

int item_scan(Item *v){
    return scanf("%d", v);
}

void item_show(Item v){
    printf("%d ", v);
}
