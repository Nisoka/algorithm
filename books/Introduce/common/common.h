#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>


extern int __log_level;

#define NLOG(str, level) {if(level > __log_level) cout << __FILE__<<": " << __func__<<"(): > "<< endl <<"\t"<< str << endl;}

int random_int();



#endif
