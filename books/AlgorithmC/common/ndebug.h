#ifndef NDEBUG_H
#define NDEBUG_H

#include <stdio.h>
#include <stdlib.h>

#define N_DEBUG 1

#if N_DEBUG == 1

#define N_DEBUG_LEVEL   10

#define nlog(func_name, str)   nlogn(func_name, str, 5)
void    nlogn(char* func_name, char *log_message, int log_level);

#else

#define nlog(a, b)
#define nlogn(a, b, c)
#endif




#endif // NDEBUG_H
