#include "ds-heap.h"


template<class KeyType, class DataType>
Heap<KeyType, DataType>::Heap()
    :heap_size_(0)
{

}

template<class KeyType, class DataType>
void Heap<KeyType, DataType>::Insert(DataItem<KeyType, DataType> item)
{

    dataManager.Insert(heap_size_, item);
    heap_size_ += 1;
    ShiftUp(heap_size_-1);
}




template<class KeyType, class DataType>
bool Heap<KeyType, DataType>::Maximum(DataItem<KeyType, DataType> &item)
{
    if(dataManager.GetVecLength() < 1 || heap_size_ < 1)
        return false;

    item.data.SetValue(dataManager.GetItem(0).data.GetValue());
    item.key.SetValue(dataManager.GetItem(0).key.GetValue());
    return true;
}

template<class KeyType, class DataType>
bool Heap<KeyType, DataType>::ExtractMax(DataItem<KeyType, DataType> &item)
{
    if(Maximum(item)){
        dataManager.Exchange(0, heap_size_-1);
        heap_size_--;
        MaxHeapify(0);
        return true;
    }else
        return false;

}

template<class KeyType, class DataType>
void Heap<KeyType, DataType>::PrintHeapData()
{
    dataManager.PrintDataItemVector(heap_size_);
}

template<class KeyType, class DataType>
int Heap<KeyType, DataType>::GetIndexOfKey(KeyType key)
{
    return dataManager.GetIndexOfKey(key);
}

template<class KeyType, class DataType>
void Heap<KeyType, DataType>::SetIndexKey(int index, KeyType newKey)
{
    dataManager.SetIndexKey(index, newKey);
}


template<class KeyType, class DataType>
void Heap<KeyType, DataType>::MaxHeapify(int heap_head)
{
    int l = HEAP_LEFT(heap_head);
    int r = HEAP_RIGHT(heap_head);
    int largest = heap_head;

    if(l < heap_size_ && dataManager.Bigger(l, largest))
        largest = l;

    if(r < heap_size_ && dataManager.Bigger(r, largest))
        largest = r;


    if(largest != heap_head){
        dataManager.Exchange(largest, heap_head);
        MaxHeapify(largest);
    }
}

template<class KeyType, class DataType>
bool Heap<KeyType, DataType>::ShiftUp(int index)
{
    bool ret = false;
    if(heap_size_ > index)
        ret = true;

    int index_parent = HEAP_PARENT(index);
    while(index > 0 && dataManager.Bigger(index, index_parent)){
        dataManager.Exchange(index, index_parent);
        index = index_parent;
        index_parent = HEAP_PARENT(index);
    }

    return ret;

}

template<class KeyType, class DataType>
bool Heap<KeyType, DataType>::ShiftDown(int index)
{
    bool ret = false;
    if(heap_size_ > index)
        ret = true;

    MaxHeapify(index);
    return ret;
}



template<class KeyType, class DataType>
void Heap<KeyType, DataType>::HeapSort()
{
    while(heap_size_ > 0){
        dataManager.Exchange(0, heap_size_-1);
        heap_size_ -= 1;
        MaxHeapify(0);
    }

    dataManager.PrintDataItemVector();
}






template<class KeyType, class DataType>
void Heap<KeyType, DataType>::Debug_BuildHeap(int size)
{

    heap_size_ = size;
    dataManager.CleanDataItemVector();
    dataManager.GenDataItemVector(size);

    // 最深底层 子堆的根节点 为 heap_size, 同级别的都是单根节点，已经堆化
    // 次深底层 的堆 为 HEAP_PARENT(heap_size_ - 1).
    // 实际完全可以 直接从 heap_size_ --> 0 直接进行全部堆化, 不过这样浪费时间.
    for(int i = HEAP_PARENT(heap_size_-1); i >= 0; i--){
        MaxHeapify(i);
    }
    dataManager.PrintDataItemVector();
}

template<class KeyType, class DataType>
void Heap<KeyType, DataType>::Debug_TestFunc()
{
    Debug_BuildHeap(10);

    DataItem<KeyType, DataType> item;
    if(ExtractMax(item)){
        printf("ExtractMax : \n");
        PrintHeapData();
    }

    item.Print();





}

