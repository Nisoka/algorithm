#ifndef DSPRIQUEUE_H
#define DSPRIQUEUE_H

#include "ds-heap.h"

template<class KeyType, class DataType>
class PriorityQueue
{
public:
    PriorityQueue();

    void Insert(DataItem<KeyType, DataType> item);
    bool ExtractMax(DataItem<KeyType, DataType> &item);
    bool GetMaxItem(DataItem<KeyType, DataType> &item);
    bool IncreaseKey(KeyType oldkey, KeyType newkey);





    DataItem<KeyType, DataType> GetMaximum();



private:
    Heap<KeyType, DataType> ds_heap_;
};

#endif // DSPRIQUEUE_H
