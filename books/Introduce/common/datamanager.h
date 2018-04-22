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
    DataItem<KeyType, DataType> ExtractItem(int i);
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


#endif // DATAMANAGER_H
