#include <stdlib.h>
#include <stdio.h>

#include "../common/link_base.h"


void josephus(int cnt, int del_n){
    int i;
    link s = link_malloc();
    s->item = 1;
    s->next = NULL;
    link t = s;
    link d = NULL;
    for(i = 2; i <= cnt; i++){
        t->next = link_malloc();
        t->next->item = i;
        t = t->next;
        t->next = s;
    }

    //t->next = s;
    //print t->next->item.  t = t->next; until t->next = s
    do{
        print_item(t->next->item);
        t = t->next;
    }while(t->next != s);
    nprint_n;

    while(t != t->next){
        for(i = 1; i < del_n; i++){
            t = t->next;
        }
        d = t->next;
        t->next = t->next->next;
        free(d);
    }
    printf("result is %d \n", t->item);
}





void link_reverse(){
    link s = link_create(10, 0);
    link b = NULL;
    link cur = s;
    link n = NULL;

    do{
        n = cur->next;
        cur->next = b;
        b = cur;
        cur = n;
    }while(n != NULL);
    s = b;
    link_print(s);
}

void sort_insert_link(){
    link s = link_create(10, 1);
    link head = link_malloc();
    link cur = s;
    link t;
    head->next = NULL;
    while(cur != NULL){
        s = cur->next;
        link sorted = head;
        while(sorted->next != NULL){
            if(sorted->next->item > cur->item){
                break;
            }
            sorted = sorted->next;
        }
        t = sorted->next;
        sorted->next = cur;
        cur->next = t;

        cur = s;
    }

    link_print(head->next);
}

int main(int argc, char* argv[]){
    sort_insert_link();
}
