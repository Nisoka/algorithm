#ifndef HEAPSORT_H
#define HEAPSORT_H
#include "common/common_int.h"
#include "common_heap.h"

using namespace std;
using namespace nan_int;




class HeapSort
{
public:
    HeapSort();
    virtual ~HeapSort();

    void MAX_HEAPIFY(int *heap_array, int heap_head);
    void BUILD_MAX_HEAP(int *heap_array);
    void HEAP_SORT(int *heap_array, int length);

    void Test_Func();


private:
    int length_;
    int heap_size_;
};


class PriorityQueue : public HeapSort
{
public:
    PriorityQueue();

    void INSERT(int *heap_array, int element);
    void MAXIMUM(int *heap_array);
    void EXTRACT_MAX(int *heap_array);
    void INCREASE_KEY(int *heap_array, int element, int new_value);

};

#endif // HEAPSORT_H
