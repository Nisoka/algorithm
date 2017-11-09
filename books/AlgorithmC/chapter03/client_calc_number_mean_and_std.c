#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "blibs/number_int.h"
//#include "number_float.h"

//计算Number类型随机数的 mean 和 std(标准差)
void calc_random_mean_and_std(int rand_len){
    int i = 0;
    float mean = 0.0;
    float std = 0.0;
    Number x;
    for(i = 0; i < rand_len; i++){

      x = randNum();
      printf(" %d",(int)x);
      mean += ((float) x)/rand_len;
      std += ((float) x*x)/rand_len;
    }
    printf("\n");
    std = sqrt(std - mean*mean);
    printf("Average is %.2f, std is %.2f \n", mean, std);
}

int main(int argc, char *argv[]){
    int paramter = atoi(argv[1]);
    calc_random_mean_and_std(paramter);
}



