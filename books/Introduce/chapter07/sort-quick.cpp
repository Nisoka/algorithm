#include "sort-quick.h"

sort_quick::sort_quick()
{

}

void sort_quick::DebugQuickSort()
{
    sort_len_ = 10;
    dataManager.GenDataItemVector(sort_len_);
    dataManager.PrintDataItemVector();
    quickSort(0, sort_len_-1);
    dataManager.PrintDataItemVector();
}

int sort_quick::quickSortPartion(int l, int r)
{
//    DataItem<nint, nint> itemMid = dataManager.GetItem(r);
    int i = l;
    // pos 保存的是 itemMid 最终位置
    // 算法:
    //（循环不变式
    //      1 l - pos之间的元素 < itemMid
    //      2 pos - i 之间的元素 >= itemMid
    //      3 i == r 时, 保持上式， 并exchange(pos, i) 完成 itemMid的最终位置。
    // 1 初始化:
    //   pos=l, i=l
    //   l - pos 之前无item, 认为 l - pos 元素 < itemMid
    //   pos - i 无item, 认为 pos - i 元素 < itemMid
    // 2 循环增加i
    // < itemMid
    //          exchange(itemL, itemPos); pos++;
    //          itemL 放到pos之前，
    // > itemMid 的itemR 放到pos之后，
    //          pos 不变，
    //          itemR 保持放在pos之后，
    // 3 当增加到 r
    // exchange(pos, r) 完成。

    int pos = l;
    char log[100] = "";
    while(i < r){
        if(!dataManager.Bigger(i, r)){
//            sprintf(log, "%d <-> %d", i, pos);
//            NLOG(log, 3);
            dataManager.Exchange(i, pos);
            dataManager.PrintDataItemVector();
            pos++;
        }
        i++;
    }
    dataManager.Exchange(pos, r);

    return pos;
}

void sort_quick::quickSort(int l, int r)
{
    if(l < r){
        int mid = quickSortPartion(l, r);
        quickSort(l, mid-1);
        quickSort(mid, r);
    }
}
