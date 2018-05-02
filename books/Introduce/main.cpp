#include <iostream>
#include "common/common_int.h"
#include "common/base_types.h"
#include "common/datamanager.h"
#include "chapter04/sub_array.h"
#include "chapter06/heapsort.h"
#include "chapter06/ds-heap.cpp"
#include "chapter06/ds-pri-queue.cpp"
#include "chapter07/sort-quick.h"


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


    sort_quick quick;
    quick.DebugQuickSort();




    return 0;
}
