#ifndef COMMON_HEAP_H
#define COMMON_HEAP_H


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

#define HEAP_PARENT(i) (int(floor((i)/2)))
#define HEAP_LEFT(i) (2*(i)+1)
#define HEAP_RIGHT(i) (2*(i)+2)

#endif // COMMON_HEAP_H
