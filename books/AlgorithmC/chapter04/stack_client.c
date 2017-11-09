#include "stack_client.h"
#include <string.h>

//need item = int;
void suffix_multiply_and_add(char *a){
    int N = strlen(a);
    int i = 0;
    printf("%d \n", N);
    for(i = 0; i < N; i++){
        printf("%c ", a[i]);
        if(a[i] == '+'){
            stack_push(stack_pop()+stack_pop());
        }

        if(a[i] == '*'){
            stack_push(stack_pop()*stack_pop());
        }

        //这个push(0) 的操作是为了下面通过循环构建一个整数的准备. 不然在循环里面需要if降低了效率
        if((a[i] >= '0') && (a[i] <= '9'))
            stack_push(0);
        while((a[i] >= '0')&& (a[i] <= '9')){
            stack_push(10*stack_pop() + (a[i++] - '0'));
        }
    }

    printf("result is %d \n", stack_pop());
}

//need item = char;
void infix_trans_to_suffix(char *a){
    int i = 0;
    int N = strlen(a);
    stack_init(N);
    for(i = 0; i < N; i++){
        if(a[i] == ')')
            printf("%c ", stack_pop());
        if(a[i] == '+' || a[i] == '*')
            stack_push(a[i]);
        if((a[i] >= '0') && (a[i] <= '9'))
            printf("%c ", a[i]);
    }

    printf("\n");
}


int main(int argc, char* argv[]){
    char *buffer = "5 9 8 + 4 6 * * 7 + *";
    //17 24 1111
    suffix_multiply_and_add(buffer);
}
