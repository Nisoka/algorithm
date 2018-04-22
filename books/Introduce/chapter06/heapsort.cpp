#include "heapsort.h"



HeapSort::HeapSort()
{
    printf("In %s\n", __FUNCTION__);
    length_ = 0;
    heap_size_ = 0;
}

HeapSort::~HeapSort()
{
}


void HeapSort::BUILD_MAX_HEAP(int *heap_array)
{
    heap_size_ = length_-1;
    // 循环不变式 能够证明算法的正确性
    // 1 初始化, i 在 a_[n/2] 之后的节点,根据堆属性, 所有heap_array[n/2]之后的元素都是叶节点， 因而是单元素堆的根, 完成了堆化
    // 2 保持, 循环堆化操作, 每次循环结束 i i+1 i+2 .. 2i 2i+1 ... n 都完成堆化（因为i 从n/2 downto 1）
    //    在for MAX_HEAPIFY(i) 之后 i+1 i+2 ... n 节点都会保持堆化, 这是循环不变量, 循环过程会保持， 因而证明算法的正确性.
    // 3 终止, 最终i = 0 最后一次循环, 根据循环不变式 算法会保证 0 1 2 ... n 的堆化属性.

    // 通过证明, 堆化的时间复杂度 实际为 O(n).

    for(int i = HEAP_PARENT(length_-1); i >= 0; i--){
        MAX_HEAPIFY(heap_array, i);
        print_array_int(heap_array, length_);
    }

}

void HeapSort::HEAP_SORT(int *heap_array, int length)
{
    length_ = length;
    heap_size_ = 0;
    BUILD_MAX_HEAP(heap_array);
    // 将最大值（堆根） 数组最后一个值交换位置, 则形成排序
    // 最后位置逐渐前移, 完成排序.
    for(int i = length_-1; i > 0; i--){
        EXCH_INT(heap_array[0], heap_array[i]);
        heap_size_ -= 1;
        MAX_HEAPIFY(heap_array, 0);
    }


}

void HeapSort::MAX_HEAPIFY(int *heap_array, int heap_head)
{
    int l = HEAP_LEFT(heap_head);
    int r = HEAP_RIGHT(heap_head);
    int larger_i = heap_head;

    if(l <= heap_size_ && heap_array[l] > heap_array[heap_head])
        larger_i = l;

    // 当时出错在, 使用逐步调试方法, 先调试了 HEAP_PARENT, 然后调试了MAX_HEAPIFY
    // MAX_HEAPIFY 在一次执行中对了, 以为问题出在别处, 当使用循环跑就出错
    // 排查结果, 找最大值做根时 出错了.
//    if(r <= heap_size_ && heap_array[r] > heap_array[heap_head])
    if(r <= heap_size_ && heap_array[r] > heap_array[larger_i])
        larger_i = r;

    if(larger_i != heap_head){
        EXCH_INT(heap_array[heap_head], heap_array[larger_i]);
        MAX_HEAPIFY(heap_array, larger_i);
    }
}


void HeapSort::Test_Func(){
    int test_len = 10;
    int *heap_array = (int *)malloc(test_len * sizeof(int));

    generate_array_int_for_debug(heap_array, test_len);

    HEAP_SORT(heap_array, test_len);

    print_array_int(heap_array, test_len);
}




PriorityQueue::PriorityQueue()
{

}
