#include "sub_array.h"

SSubArrayInfo::SSubArrayInfo()
    :left(0),right(0),sum(0)
{

}

SSubArrayInfo::SSubArrayInfo(int l, int r, int s)
{
        {
            left = l;
            right = r;
            sum = s;
        }
}

sub_array::sub_array()
{
    vec_len = 25;
    generate_vec_int(&vec_data, vec_len);
}

struct SSubArrayInfo sub_array::find_max_cross_subarray(vector<int> *vec_data, int low, int mid, int high)
{
    int left_sum = -SENTINEL_INT;
    int right_sum = -SENTINEL_INT;
    int start = 0;
    int end = 0;
    int sum = 0;
    int i = 0;
    for(i = mid; i >= low; i--){
        sum += (*vec_data)[i];
        if(sum > left_sum){
            left_sum = sum;
            start = i;
        }
    }

    sum = 0;
    for(i = mid+1; i<= high; i++){
        sum += (*vec_data)[i];
        if(sum > right_sum){
            right_sum = sum;
            end = i;
        }
    }

    return SSubArrayInfo(start, end, (left_sum+right_sum));
}

SSubArrayInfo sub_array::find_maximum_subarray(vector<int> *vec_data, int low, int high)
{
    SSubArrayInfo left_res, right_res, cross_res;

    if(high == low){
        return SSubArrayInfo(low, high, (*vec_data)[low]);
    }
    else{
        //mid - left_end_pos;
        //mid+1 - right_start_pos;
        int mid = (low + high)/2;
        left_res = find_maximum_subarray(vec_data, low, mid);
        right_res = find_maximum_subarray(vec_data, mid+1, high);
        cross_res = find_max_cross_subarray(vec_data, low, mid, high);

        if(left_res.sum >= right_res.sum && left_res.sum >= cross_res.sum)
            return left_res;
        else if(right_res.sum >= left_res.sum && right_res.sum >= cross_res.sum)
            return right_res;
        else
            return cross_res;
    }
}

SSubArrayInfo sub_array::find_maximum_subarray_brute_force_attach(vector<int> *vec_data)
{
    int start, end, res_start, res_end;
    int len = vec_data->size();
    int sum = -MAX_INT;
    int maxium_value = -MAX_INT;

    for(start = 0; start < len ; start ++){
        for(end = start; end < len; end ++){
            sum = 0;
            for(int i = start; i <= end; i ++){
                sum += vec_data->at(i);
            }
            if(sum > maxium_value){
                maxium_value = sum;
                res_start = start;
                res_end = end;
            }
        }
    }


    return SSubArrayInfo(res_start, res_end, maxium_value);
}



void sub_array::test_Func()
{
    SSubArrayInfo res =  find_maximum_subarray(&vec_data, 0, vec_len-1);

    printf("result is %d, %d, %d\n", res.left, res.right, res.sum);



    res = find_maximum_subarray_brute_force_attach(&vec_data);
    printf("result is %d, %d, %d\n", res.left, res.right, res.sum);
}




