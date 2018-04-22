#include <iostream>
#include "common/common_int.h"
#include "chapter04/sub_array.h"
#include "chapter06/heapsort.h"
#include "chapter06/ds-heap.cpp"
#include "common/base_types.h"
#include "common/datamanager.cpp"
using namespace std;
using namespace nan_int;

template<class T>
class CTest
{
public:
    CTest(T i){value = i;}
    T GetVal(){return value;}
    T value;
};

void TestFunc(){
    vector<CTest<int>> vec;
    for(int i = 0; i < 10; i ++){
        vec.push_back(CTest<int>(i));
    }

    vec.erase(vec.begin()+2);

    for(int i = 0; i < vec.size(); i++)
        printf("-%d-", vec[i].GetVal());
}


int main()
{
    nanDebug::isDebuging = true;


    Heap<nint, nint> ds_heap;
    ds_heap.Debug_TestFunc();

    return 0;
}
