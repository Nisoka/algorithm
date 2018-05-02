#ifndef SORTQUICK_H
#define SORTQUICK_H

#include "common/datamanager.h"


class sort_quick
{
public:
    sort_quick();

    void DebugQuickSort();

    int quickSortPartion(int l, int r);
    void quickSort(int l, int r);

private:
    DataManager<nint, nint> dataManager;
    int sort_len_;
};

#endif // SORTQUICK_H
