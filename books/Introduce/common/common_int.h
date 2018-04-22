#ifndef COMMON_INT
#define COMMON_INT

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include "common.h"

int random_int();

using namespace std;
namespace nan_int {


#define MAX_INT 200
#define SENTINEL_INT 65535


#define EXCH_INT(A, B) {int t = A; A = B; B = t;}
#define EXCH_ITEM(A, B) {Item t = A; A = B; B = t;}


typedef int keyType;
typedef int valType;

typedef struct{
    keyType key;
    valType value;
}Item;








void generate_array_int_for_debug(int a[], int length);

void generate_array_int(int a[], int length);
void print_array_int(int a[], int length);

void generate_vec_int(vector<int> *a, int length);
void print_vec_int(vector<int> a);




}

#endif
