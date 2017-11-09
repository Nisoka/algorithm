#include "item_adt.h"


#ifdef RECORD_SORT_KEY_NUM
int less(Item a, Item b)
{
    return a->num < b->num;
}

#elif (defined RECORD_SORT_KEY_NAME)
int less(Item a, Item b)
{
    return strcmp(a->name, b->name) < 0;
}

#elif (defined RECORD_SORT_MULTI_KEY)
int less(Item a, Item b)
{
    if(a->num < b->num){
        return 1;
    }else{
        return strcmp(a->name, b->name) < 0;
    }
}
#endif

struct record data[100000];
int Nrecs = 0;


Item item_rand(){
  return NULL;
}
int  item_scan(Item *v){
  *v = &data[Nrecs];
  return scanf("%30s %d", data[Nrecs].name, data[Nrecs++].num);
}
void item_show(Item v){
  printf("%-30s - %d\n", v->name, v->num);
}
