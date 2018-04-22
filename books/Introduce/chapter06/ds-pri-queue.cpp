#include "ds-pri-queue.h"

template<class KeyType, class DataType>
PriorityQueue<KeyType, DataType>::PriorityQueue()
{

}

template<class KeyType, class DataType>
void PriorityQueue<KeyType, DataType>::Insert(DataItem<KeyType, DataType> item)
{
    ds_heap_.Insert(item);
}

template<class KeyType, class DataType>
bool PriorityQueue<KeyType, DataType>::ExtractMax(DataItem<KeyType, DataType> &item)
{
    return ds_heap_.ExtractMax(item);
}

template<class KeyType, class DataType>
bool PriorityQueue<KeyType, DataType>::GetMaxItem(DataItem<KeyType, DataType> &item)
{
    return ds_heap_.Maximum(item);
}

template<class KeyType, class DataType>
bool PriorityQueue<KeyType, DataType>::IncreaseKey(KeyType oldkey, KeyType newkey)
{
    int index = ds_heap_.GetIndexOfKey(oldkey);
    ds_heap_.SetIndexKey(index, newkey);
    if(newkey > oldkey){
        return ds_heap_.ShiftUp(index);
    }else{
        return ds_heap_.ShiftDown(index);
    }

}
