#ifndef SUB_ARRAY_H
#define SUB_ARRAY_H

#include "common/common_int.h"
using namespace nan_int;

class SSubArrayInfo{
public:
    int left;
    int right;
    int sum;

    SSubArrayInfo();
    SSubArrayInfo(int l, int r, int s);

};

class sub_array
{
public:
    sub_array();

    SSubArrayInfo find_max_cross_subarray(vector<int> *vec_data,int low, int mid, int high);
    SSubArrayInfo find_maximum_subarray(vector<int> *vec_data, int low, int high);
    SSubArrayInfo find_maximum_subarray_brute_force_attach(vector<int> *vec_data);

    void test_Func();

private:
    int vec_len;
    vector<int> vec_data;

    SSubArrayInfo result_subarray;

};

#endif // SUB_ARRAY_H
