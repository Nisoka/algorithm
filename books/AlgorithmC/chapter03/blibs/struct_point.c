#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "struct_point.h"

struct __point{
  float x;
  float y;
};

float randFloat(float maxValue)
{
  return maxValue * rand()/RAND_MAX;
}

//指针的指针
//参数传递 都是值传递，a传入函数后 a就是一个临时变量，所以传入的a必需是一个地址才能将数据返回回去。。。。。
void  point_malloc(point *a){
  *a = malloc(sizeof(struct __point));
}

void  point_free(point *a){
  free(*a);
}

void  point_print(point a){
  printf("x: %f, y: %f \n", a->x, a->y);
}

void  point_initial(point a, float maxV){
  a->x = randFloat(maxV);
  a->y = randFloat(maxV);    
}

float distance(point a, point b){
  float dx = a->x - b->x;
  float dy = a->y - b->y;
  return sqrt(dx*dx + dy*dy);
}
