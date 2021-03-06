#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <assert.h>
#include "common_int.h"
#include "base_types.h"
#include "nan_debug.h"
//baidu MiMa3372




template<class KeyType, class DataType>
class DataItem
{
public:
    DataItem(){}
    DataItem(KeyType k, DataType d);


    void Print();


    DataItem& operator=(DataItem& obj1);


public:
    KeyType key;
    DataType data;
};




template<class KeyType, class DataType>
class DataAllocator
{
public:
    DataAllocator();

    void GenItemDataArray(DataItem<KeyType, DataType> *item, int length);
    void GenItemDataVector(vector<DataItem<KeyType, DataType> > &item_vec);

    void SetDebug(bool debug){debug_ = debug;}

private:
    bool debug_;

};



template<class KeyType, class DataType>
class DataManager
{
public:
    DataManager();
    virtual ~DataManager();

    //Array
    void GenDataItemArray(int length);
    void PrintDataItemArray();
    void GetArrLength(){return arr_len_;}
    void SetArrLength(int length){arr_len_ = length;}

    //Vector
    DataItem<KeyType, DataType> GetItem(int i);
    DataItem<KeyType, DataType> ExtractItem(int pos);
    void Insert(int pos, DataItem<KeyType, DataType> item);
    void Append(DataItem<KeyType, DataType> item);
    int GetVecLength(){return item_vec_.size();}


    void GenDataItemVector(int length);
    void CleanDataItemVector();
    void PrintDataItemVector(int size = 0);

    int GetIndexOfKey(KeyType key);
    void SetIndexKey(int index, KeyType newKey);
    bool Bigger(int indexi, int indexj);
    void Exchange(int indexi, int indexj);


    void DebugTest();

    enum DataSave{
        eDataSaveAsArray = 0,
        eDataSaveAsVector
    };
public:
    int _data_save_as_type;

    DataAllocator<KeyType, DataType> allocator_;

    DataItem<KeyType, DataType> item_;
    DataItem<KeyType, DataType> *item_arr_;

    vector<DataItem<KeyType, DataType>> item_vec_;
    vector<DataItem<KeyType, DataType>> item_vec_temp_;
    int arr_len_;

    DataItem<KeyType, DataType> **item_matrix_;
    int matrix_len_;
};



template<class KeyType, class DataType>
DataItem<KeyType, DataType>::DataItem(KeyType k, DataType d)
    :key(k), data(d)
{

}



template<class KeyType, class DataType>
DataItem<KeyType, DataType> &DataItem<KeyType, DataType>::operator=(DataItem &obj1)
{
    this->key = obj1.key;
    this->data = obj1.data;

    return *this;
}

template<class KeyType, class DataType>
void DataItem<KeyType, DataType>::Print()
{
    this->key.Print();
    printf(",");
    this->data.Print();
    printf(" ");
}











template<class KeyType, class DataType>
DataManager<KeyType, DataType>::DataManager()
    :item_arr_(NULL), item_matrix_(NULL), arr_len_(0), matrix_len_(0)
{
    _data_save_as_type = eDataSaveAsVector;
}
template<class KeyType, class DataType>
DataManager<KeyType, DataType>::~DataManager()
{

    if(item_arr_ != NULL){
//        delete item_arr_; 这种方式, 会删除对象的内存空间,
//        但只会对 item_arr_[0] 调用析构函数, 如果内部有堆数据, 会产生内存泄漏， 所以不可用.
//        必须使用如下方式删除数组
        delete []item_arr_;
    }

    if(item_matrix_ != NULL){
//        删除多维度数组必须逐个维度的数据先进行删除, 通过简单的 delete name 的方式虽然会清空内存空间
//        但是不会清楚 类 在堆上申请的数据.
//        所以 数组 都必须 考虑 对该对象的析构.
        for(int i = 0; i < matrix_len_; i++)
            delete []item_matrix_[i];
        delete []item_matrix_;
    }
}

template<class KeyType, class DataType>
void DataManager<KeyType, DataType>::GenDataItemArray(int length)
{
    arr_len_ = length;
    item_arr_ = new DataItem<KeyType, DataType>[arr_len_];
//    item_matrix_ = new DataItem[length][length];

    allocator_.GenItemDataArray(item_arr_, arr_len_);
}

template<class KeyType, class DataType>
void DataManager<KeyType, DataType>::PrintDataItemArray()
{
    int i = 0;
    for(i = 0; i < arr_len_; i++){
        item_arr_[i].key.Print();
    }
}

template<class KeyType, class DataType>
DataItem<KeyType, DataType> DataManager<KeyType, DataType>::GetItem(int i)
{
    return item_vec_[i];
}

template<class KeyType, class DataType>
DataItem<KeyType, DataType> DataManager<KeyType, DataType>::ExtractItem(int pos)
{
    //直接使用 item_vec_.erase(iter) 方法出错, 具体原因不明, 像是库本身问题.
    typename vector<DataItem<KeyType, DataType>>::iterator iter = item_vec_.begin()+pos;
    DataItem<KeyType, DataType> item = item_vec_[pos];

    for(; iter + 1 < item_vec_.end(); iter++){
        *iter = *(iter+1);
    }
    item_vec_.resize(item_vec_.size() - 1);

    return item;
}


template<class KeyType, class DataType>
bool DataManager<KeyType, DataType>::Bigger(int indexi, int indexj)
{
    switch (_data_save_as_type) {
    case eDataSaveAsArray:
        if(item_arr_[indexi].key > item_arr_[indexj].key)
            return true;
        return false;
        break;

    case eDataSaveAsVector:
        if(item_vec_[indexi].key > item_vec_[indexj].key)
            return true;
        return false;
        break;
    default:
        break;
    }
    return false;
}

template<class KeyType, class DataType>
void DataManager<KeyType, DataType>::Exchange(int indexi, int indexj)
{

    switch (_data_save_as_type) {
    case eDataSaveAsArray:
        item_ = item_arr_[indexi];
        item_arr_[indexi] = item_arr_[indexj];
        item_arr_[indexj] = item_;
        break;

    case eDataSaveAsVector:
        item_ = item_vec_[indexi];
        item_vec_[indexi] = item_vec_[indexj];
        item_vec_[indexj] = item_;
        break;
    default:
        break;
    }
}



// pos: is the target postion. eg:0 -- 9
template<class KeyType, class DataType>
void DataManager<KeyType, DataType>::Insert(int pos, DataItem<KeyType, DataType> item)
{
    assert(_data_save_as_type == eDataSaveAsVector);
    typename vector<DataItem<KeyType, DataType>>::iterator
            iter_cur = item_vec_.end()-1,                       //vector.end() is not the last value, but the end()-1 is .
            iter_target = item_vec_.begin() + pos;

    //直接使用 item_vec_.insert(iter, item) 方法出错, 具体原因不明, 像是库本身问题.
    item_vec_.resize(item_vec_.size() + 1);
    for(; iter_cur >= iter_target; iter_cur--){
        *(iter_cur + 1) = *iter_cur;
    }
    *iter_target = item;

}

template<class KeyType, class DataType>
void DataManager<KeyType, DataType>::Append(DataItem<KeyType, DataType> item)
{
    item_vec_.push_back(item);
}

template<class KeyType, class DataType>
void DataManager<KeyType, DataType>::GenDataItemVector(int length)
{
    item_vec_.reserve(2*length);
    item_vec_.resize(length);
    allocator_.GenItemDataVector(item_vec_);
}

template<class KeyType, class DataType>
void DataManager<KeyType, DataType>::CleanDataItemVector()
{
    item_vec_.clear();
    item_vec_.resize(0);
}

// vector.begin() is the first value
// vector.end() is not the last value,  but the last+1 value.
template<class KeyType, class DataType>
void DataManager<KeyType, DataType>::PrintDataItemVector(int size)
{
    typename vector<DataItem<KeyType, DataType>>::iterator iter;
    for (iter = item_vec_.begin(); iter != item_vec_.end(); iter++){
        (*iter).Print();
        printf(" ");
    }
    printf("\n");
}

template<class KeyType, class DataType>
int DataManager<KeyType, DataType>::GetIndexOfKey(KeyType key)
{
    typename vector<DataItem<KeyType, DataType>>::iterator iter;

    int i = 0;
    for (iter = item_vec_.begin(); iter != item_vec_.end(); iter++){
        i++;
        if (iter->key.GetValue() == key.GetValue()){
            return i;
        }
    }
}

template<class KeyType, class DataType>
void DataManager<KeyType, DataType>::SetIndexKey(int index, KeyType newKey)
{
       item_vec_[index].key = newKey;
}

template<class KeyType, class DataType>
void DataManager<KeyType, DataType>::DebugTest()
{
    printf("Test Generate! \n");
    GenDataItemVector(10);
    PrintDataItemVector();

    printf("Test ExtractItem! \n");
    DataItem<KeyType, DataType> item = ExtractItem(3);
    PrintDataItemVector();

    printf("Test Instert, Append! \n");
    Insert(9, item);
    Append(item);
    PrintDataItemVector();
    printf("Cur length is 11, true is %d \n", GetVecLength());


    printf("Test GetIndexOf, SetIndexKey! \n");
    int key = 7;
    int index = GetIndexOfKey(7);
    printf(" key %d Item's index is %d \n", key, index);
    SetIndexKey(index, 17);

    PrintDataItemVector();


    item.key.SetValue(1);

}



















template<class KeyType, class DataType>
DataAllocator<KeyType, DataType>::DataAllocator()
    :debug_(false)
{

}

template<class KeyType, class DataType>
void DataAllocator<KeyType, DataType>::GenItemDataVector(vector<DataItem<KeyType, DataType> > &item_vec)
{
    int len = item_vec.size();
    if(nanDebug::isDebuging){
        for(int i = 0; i < len; i++){
            item_vec[i].key.SetValue(len - i);
            item_vec[i].data.SetValue(len - i);
        }
        return ;
    }
    for(int i = 0; i < len; i++){

        item_vec[i].key.SetRandom();
        item_vec[i].data.SetRandom();
    }
}

template<class KeyType, class DataType>
void DataAllocator<KeyType, DataType>::GenItemDataArray(DataItem<KeyType, DataType> *item, int length)
{
    if(nanDebug::isDebuging){
        for(int i = 0; i < length; i++){
            item[i].key.SetValue(i);
            item[i].data.SetValue(i);
        }
        return ;
    }


    for(int i = 0; i < length; i++){
        item[i].key.SetValue(i);
        item[i].data.SetValue(i);
    }
}



#endif // DATAMANAGER_H
