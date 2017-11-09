#include "ndebug.h"

#if N_DEBUG == 1
void nlogn(char *func_name, char *log_message, int log_level){
    if(log_level <= N_DEBUG_LEVEL)
        printf("--%d--: %s: %s\n", log_level, func_name, log_message);
}
#endif
