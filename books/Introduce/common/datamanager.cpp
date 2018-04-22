#include "datamanager.h"



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
    printf("Key is: ");
    this->key.Print();
    printf(", Value is: ");
    this->data.Print();
    printf(". ");
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

////////////////////////////////////////////////// Vector //////////////////////////////////////////////////

template<class KeyType, class DataType>
DataItem<KeyType, DataType> DataManager<KeyType, DataType>::GetItem(int i)
{
    return item_vec_[i];
}

template<class KeyType, class DataType>
DataItem<KeyType, DataType> DataManager<KeyType, DataType>::ExtractItem(int i)
{
    //直接使用 item_vec_.erase(iter) 方法出错, 具体原因不明, 像是库本身问题.
    typename vector<DataItem<KeyType, DataType>>::iterator iter = item_vec_.begin()+i;
    DataItem<KeyType, DataType> item = item_vec_[i];

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





template<class KeyType, class DataType>
void DataManager<KeyType, DataType>::Insert(int pos, DataItem<KeyType, DataType> item)
{
    assert(_data_save_as_type == eDataSaveAsVector);
    typename vector<DataItem<KeyType, DataType>>::iterator
            iter_cur = item_vec_.end(),
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

template<class KeyType, class DataType>
void DataManager<KeyType, DataType>::PrintDataItemVector(int size)
{
    int len = size;
    if(len == 0)
        len = item_vec_.size();

    for(int i = 0; i < len; i++){
        item_vec_[i].key.Print();
        printf(" ");
    }
    printf("\n");
}

template<class KeyType, class DataType>
int DataManager<KeyType, DataType>::GetIndexOfKey(KeyType key)
{
    typename vector<DataItem<KeyType, DataType>>::iterator
            iter = item_vec_.begin(),
            end = item_vec_.end();
    int i = 0;
    for(; iter != end; iter++, i++){
        if(iter->key.GetValue() == key.GetValue()){
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
    GenDataItemVector(10);
    printf("Generate! \n");
    PrintDataItemVector();

    printf("ExtractItem! \n");
    DataItem<KeyType, DataType> item = ExtractItem(3);
    PrintDataItemVector();


    printf("Instert, Append! \n");
    Insert(5, item);
    Append(item);
    PrintDataItemVector();


    printf("Cur length is 11, true is %d \n", GetVecLength());

    printf("GetIndexOf, SetIndexKey! \n");
    int index = GetIndexOfKey(7);
    printf(" ------- index %d \n", index);
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
            item_vec[i].key.SetValue(i);
            item_vec[i].data.SetValue(i);
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

