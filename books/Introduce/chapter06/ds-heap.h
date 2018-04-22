#ifndef DSHEAP_H
#define DSHEAP_H

#include "common/datamanager.h"
#include "common_heap.h"

// 算法不能离开数据结构, 因此算法应该在数据结构中.
template<class KeyType, class DataType>
class Heap
{
public:
    Heap();

//Base Operate
public:

    void MaxHeapify(int heap_head);
    bool ShiftUp(int index);
    bool ShiftDown(int index);
    //增 删 改 查
    void Insert(DataItem<KeyType, DataType> item);
    bool Maximum(DataItem<KeyType, DataType> &item);
    bool ExtractMax(DataItem<KeyType, DataType> &item);


    void PrintHeapData();


    int GetIndexOfKey(KeyType key);
    void SetIndexKey(int index, KeyType newKey);

    int HeapSize(){return heap_size_;}



public:
    // For Debug
    void Debug_BuildHeap(int size);
    void Debug_TestFunc();

private:
    DataManager<KeyType, DataType> dataManager;

    int heap_size_;

//Algorithm
public:
    void HeapSort();

};


#endif // DSHEAP_H
