#include "link_list.h"

#define CONCISE_OR_EASYTHINK    2

struct node{
    Item item;
    link next;
};


/* 3.3 链表
    对比 数组的优势: 快速重排数据的能力,
这种灵活性的代价是, 不能快速访问表中任意对象.访问对象需要沿着链表,逐个节点进行访问.
    链表不适合用于“查找第k个元素” （给定索引，查找某个元素）的操作。而相对的数组的这个操作是最高效的。
    

链表核心 基础定义:
    链表是一组数据项的集合, 其中每个数据项都是一个节点的一部分,

但是链表的实现可以根据不同需要自行决定:
    链表还可以理解为一个指向节点的链接(指针), 且该节点或者为空 或者包含一个元素和一个指向另外链表的链接.

每个节点除了数据项, 还包括指向下一个节点的链接指针.
    通过节点next引用下一个节点, 因而链表有时也被成为自引用结构.
    尽管一个节点的指针经常指向不同的节点, 但也可以用来指向自身, 所以链表也称为循环结构.


末尾节点 next == NULL;
    如果链表不形成环, 约定将末尾节点置为不指向任何节点的空指针.
    形成环, 则使其指向首节点, 得到循环链表.
    经常链表 需要一个额外不保存数据节点-哑元节点 作为链表头head, 仅用来方便链表操作不保存数据.
哑元节点
    链表在发生排序插入时, 如果插入在头结点, 需要的操作 不同于其他地方的插入,
    所有很多时候 链表都增加一个哑元节点。

    插入删除 快速, 相比较 数组需要更新剩余的所有, 这就是链表存在的原因。
    而相对的 链表 对于访问 第n个元素 访问缓慢.

所以
    经常进行 插入 删除等 要用 链表
    经常进行 访问操作 要用 数组.

理解:
链表
    节点: 实际对象
    指针: 节点内指针
    pointer         指针 (是脱离链表的 是浮动的 指向节点的 指针)
    [item, next]    节点[元素, 指针(不脱离链表的, 必须指向链表内下一个元素. 所有node->next 都必须指向下一个节点)]

*/

/* 3.4 链表的基本处理操作
   见 link_node_interface.h
   接口封装了link的底层操作link->next link->item.
   虽然封装了底层细节,但是对于link这种基本的基本数据结构来说, 并不推荐,
   因为这些最基本的逻辑操作 使用接口封装方式可能更不好.
   链式结构直接写底层操作, 可以清楚的解释算法和数据结构的核心细节.

*/

/* 3.5 链表的内存和分配
    link_node_interface.c
    (自己形成库)
    1 空闲链表 作为link_node回收机制, 这样能够迅速 创建 删除节点.

*/

//更好的实现 见link.c(将 link struct node 封装起来)

//约瑟夫问题
//循环从link_len中剔除第exclude_num个,求剩余元素.
void josephus_book(int link_len, int exclude_num){
    int i, j;
    link s = (link)malloc(sizeof(struct node));
    s->item = 1;
    link t = s;
    //循环链表
    for(i = 2; i < link_len + 1; i++){
        t->next = (link)malloc(sizeof(struct node));
        t->next->item = i;
        t = t->next;
        t->next = s;
    }

    do{
        printf("%d ", t->next->item);
        t = t->next;
    }while(t->next!=s);

    //t 要是 s的上一个.
    // 下面内部循环 是1 - exclude-1, 计数移动从s开始.
    while(t != t->next){      //循环链表唯一节点判断.
        //1 - exclude_num-1 执行结束 t->next 就是待剔除元素.
        for(i = 1; i < exclude_num; i++){
            t = t->next;
        }

        t->next = t->next->next;
        link_len--;
    }
    printf("the remain one is %d \n", t->item);
}

void josephus(int len, int exclude_num){
  link s = malloc(sizeof(*s));
  int i, j;
  link t;
  link d;
  
  s->item = 1;
  s->next = NULL;
  t = s;

  for(i = 2; i < len+1; i++){
    t->next = malloc(sizeof(*s));
    t = t->next;
    t->item = i;
    t->next = s;
  }
  
  do{
    printf("%d ", t->next->item);
    t = t->next;
  }while(t->next!=s);

  printf("\n");

  //t is the before of s.
  while(t != t->next){
    for(i = 1; i < exclude_num; i++){
      t = t->next;
    }
    d = t->next;
    t->next = d->next;
    printf("%d ", d->item);
    free(d);
  }
  printf("\nremin item is %d\n", t->item);
}



void link_reverse(int maxN){
  link s = malloc(sizeof(struct node));
  int i = 0;
  link t,b,n;
  t = s;
  s->item = 1;
  s->next = NULL;

  for(i = 2; i <= maxN; i++){
    //直接构建链表
    t = t->next = malloc(sizeof(struct node));
    t->item = i;
    t->next = NULL;
  }

  t = s;
  b = NULL;
  while(t != NULL){
    n = t->next;
    t->next = b;
    b = t;
    t = n;
  }

  s = b;
  t = s;
  while(t != NULL){
    printf("%d ", t->item);
    t = t->next;
  }
}
        

//link 插入排序
void link_insert_sort_book(int link_len){
  struct node heada, headb;
  link x;
  link y;
  link t;
  link u;
  int i = 0;


  for(i = 0, t = &heada; i < link_len; i++){
    t->next = malloc(sizeof(struct node));
    t = t->next;
    t->item = rand()%1000;
    t->next = NULL;
    printf("%d: %d ", i, t->item);
  }
  printf("\n");

  i = 0;
  //t->next == NULL; 此时t 为末尾元素。
  //如果使用t->next != NULL 为结束判断, 则最后的t 被跳过了.
  //要时刻注意, 链表的next指向的是下一个节点. 而link_node本身是一个节点.
  //可以这么思考链表 如果 t!=NULL, 则t->item还有数据.
  //               同理 t->next != NULL, 则t->next->item 还有数据
  for(t = (&heada)->next; t != NULL; t = t->next){
    printf("%d: %d ",i++, t->item);
  }
  printf("\n");

  headb.next = NULL;
  headb.item = 999;

  //x != NULL, 说明当前是个节点,还可遍历操作
  //当x == NULL, 说明已经跳出末尾节点, 已经完成了.
  for(x = (&heada)->next; x != NULL; x = u){
      u = x->next;

      /* 插入排序, 遍历 找第一个大于待插入元素的节点.
      查找 插入.
      基本原理:
          找到第一个大于 x->item的y_node, 在它前面插入x。
          需要 y_node的上一个节点y_last_node.
      特殊位置:
          末尾: 此时没有 大于 x->next的y_node,所以遍历结束后 末尾节点 即 y_node->next == NULL;
          开始: 同于末尾, 因为有head 所以 head->next == NULL, 直接插入到head->next 即可.
       */
#if CONCISE_OR_EASYTHINK == 1
      /* 简洁查找、插入.
        这个简洁算法充分考虑了问题重点--
          1 前一个元素用来插入.  y_last.
          2 下一个元素的item 用来判断, 或者说只需要y->next->item就可以了
        用y->next!=NULL, y->next->item > x->item进行判断,y本身就保存的是y_last_node。
      */

      /* 问题的重点是 需要 保存前一个元素
          1 前一个元素用来插入. ***** 必须保存node本身指针, 后一个node获得不到前一个node
          2 下一个元素的item 用来判断, 可以通过前一个node获得.
          这种情况下更应该使用y->next!=NULL ; y->next->item来判断.
          需要 前一个元素 的情况时 应该使用y->next!=NULL, 进行遍历. y->next->item 进行判断.
      */
      for(y = &headb; y->next!=NULL; y = y->next){
          if(y->next->item > x->item)
              break;
      }
      x->next = y->next;
      y->next = x;
#else

      /* 这问题 重点是需要保存前一个元素.
        使用y!=NULL;判断结束,
        使用y->item判断位置, 那么就多需要一个y_last来保存上一个元素node.
      */
      t = &headb;
      for(y = (&headb)->next; y!=NULL; y = y->next){
          if(y->item > x->item)
              break;
          //增加代码来保存上一个元素. 这是问题重点没有搞清 给算法增加负担的.
          t = y;
      }
      x->next = y;
      t->next = x;
#endif
  }

  i = 0;
  for(t = (&headb)->next; t != NULL; t = t->next){
    printf("%d: %d ",i++, t->item);
  }

}


void link_insert_sort(int maxN){
  int i, j;
  link t, a, b, n, t2;
  struct node heada, headb;

  a = &heada;
  b = &headb;

  a->next = NULL;
  b->next = NULL;


  for(i = 1, t = a; i <= maxN; i++){
    t = t->next = malloc(sizeof(struct node));
    t->item = rand()%20;
    t->next = NULL;
  }

  t = a->next;
  while(t != NULL){
    printf("%d ", t->item);
    t = t->next;
  }
  printf("\n");

  t = a->next;
  while(t != NULL){
    n = t->next;

    for(t2 = b; t2->next != NULL; t2 = t2->next){
      if(t2->next->item > t->item)
        break;
    }
    t->next = t2->next;
    t2->next = t;
    t = n;
  }

  t = b->next;
  while(t!=NULL){
    printf("%d ", t->item);
    t = t->next;
  }
  printf("\n");

}


int main(int argc, char *argv[]){
    int input_paramter_1 = atoi(argv[1]);
//    int input_paramter_2 = atoi(argv[2]);
//    josephus(input_paramter_1, input_paramter_2);
//    remain_in_link_book(input_paramter_1, input_paramter_2);
//    remain_in_link(input_paramter_1, input_paramter_2);
    link_insert_sort(input_paramter_1);
}

