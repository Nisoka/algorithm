#ifndef STRUCT_POINT_H
#define STRUCT_POINT_H

typedef struct __point* point;
void  point_malloc(point *a);
void  point_free(point *a);
void  point_print(point a);
void  point_initial(point a, float maxV);
float distance(point, point);

#endif
