#include "radix_sort.h"

/*
    10.2 二进制快排
    从第0位开始进行排序, 前位比较就能进行排序, 如果相同则进行后位比较.
    递归进行 则实现排序.
*/
void binary_quick_sort_kernel(int a[], int l, int r, int w)
{
    int i = l;
    int j = r;
    if(r <= l || w > bitsword)
        return ;
    //指针未相遇时
    while(j != i){
        //从左起, 如果位为0, 并且i < j 左右指针未相遇, 继续寻找
        while(digit(a[i], w) == 0 && (i < j))
            i++;
        while(digit(a[j], w) == 1 && (j > i))
            j--;
        //找到a[i] = 1 a[j] = 0 则交换
        exch(a[i], a[j]);
    }
    //保证j 为a的第w位=1的最开始索引
    if(digit(a[r], w) == 0)
        j++;

    binary_quick_sort_kernel(a, l, j-1, w+1);
    binary_quick_sort_kernel(a, j, r, w+1);
}

void binary_quick_sort(int a[], int l, int r){
    binary_quick_sort_kernel(a, l, r, 0);
}




/*
    10.3 MSD基数排序
    桶排序
        1 要先确定桶数目 R 这样才能定义索引统计数组count 来进行索引统计.
    因为关键字最高权重位在前, 所以不能使用LSD那样 从右向左对 每一位索引技术统计排序, 而达到排序目的.
        因为LSD 是最后的最高权重位在最后使用, 所以影响最大, 最后使用即可完成排序.
    而MSD先使用最高权重位, 必须要将最高权重位的重要性表达出来, 必须最高权重位分割成桶 就只需要排序内部的数据即可,
        不可再对不同桶内的数据进行排序, 所以需要使用递归实现桶内排序.
        这样情况下 时间复杂度就是 N*(bytesword)???  不理解.
        并且MSD会产生大量空桶, 需要被优化掉.
*/
#define bin(A) l+count[A]
#define M 10
/*
    R个关键字内控制字所有可能值(局部的所有可能取值, 对字符串,每个字符可能取值就是a-z 26个可能取值)
    R个桶, 装下了所有文件,将文件分装起来,然后按照第二个部分继续进行, 最后会排序完成
 */
#define R 26
Item aux[10000];
void radixMSD(Item a[], int l, int r, int w){
    int i, j, count[R+1];
    if(w > bytesword)
        return ;
    if(r-l <= M){
        insert_sort(a, l, r);
        return ;
    }
    for(j = 0; j < R; j++)
        count[j] = 0;

    //统计所有w位值为index的a[i]的个数.
    for(i = l; i <= r; i++)
        count[digit(a[i], w) + 1]++;
    //将count 作为每个a的位置index 所以需要逐个向上累加.
    for(j = 1; j < R; j++)
        count[j] += count[j-1];

    //aux拷贝数组, 将a[i] 按照局部关键字索引统计方法拷贝进入aux进行多重复关键字排序.
    for(i = l; i <= r; i++)
        aux[count[digit(a[i], w)]++] = a[i];
    //拷贝回来, 排序就完成了.
    for(i = l; i <= r; i++)
        a[i] = aux[i-1];

    //对第一次划分了相同局部关键字 进行递归下一个局部关键字
    radixMSD(a, l, bin(0)-1, w+1);
    for(j = 0; j < R-1; j++)
        radixMSD(a, bin(j), bin(j+1)-1, w+1);
}

/*
10.4 三路基数快速排序
    另一种使用快排 进行MSD基数排序的方法是 对关键字控制字节进行三路划分.
    三路划分 会形成将控制字按照 小于 等于 大于。 而只有在等于时 在进行下一个控制字的基数排序.
    递归对 小于 大于的剩余序列执行三路划分后基数快速排序.
*/

#define ch(A) digit(A, D)
void quick_sort_3path(Item a[], int l, int r, int D){
  int i, j, k, p, q;
  int v;
  if(r-l <= M){
    insert_sort(a, l, r);
    return ;
  }
  // 快排 比较关键字 v
  v = ch(a[r]);
  //几个 pos指针
  i = l-1;
  j = r;
  p = l-1;
  q = r;
  
  while(i < j){
    //快排 核心： i从左找到 不小于v的值，j从右找 不大于v的值
    //交换 循环进行， 直到 i j相遇，则v在i位置就是最终位置
    while( ch(a[++i]) < v ) ;
    while( v < ch(a[--j]) )
      if(j == l)
        break;
    if(i > j)
      break;

    exch(a[i], a[j]);
    //当前a[i]==v, 相同关键字值，则与当前最左元素交换
    if(ch(a[i]) == v){
      p++;
      exch(a[p], a[i]);
    }
    if(v == ch(a[j])){
      q--;
      exch(a[q], q[j]);
    }
  }
  //p q相遇说明 全部关键字都相同，递归下一个控制字D＋1 进行三路快排序
  if(p == q){
    if(v!='\0')
      quick_sort_3path(a, l, r, D+1);
  }
  
  //因为选择使用最后元素a[r]作为 快排比较关键字， 所以最后a[r]的位置是大于左边所有元素，小于右所有元素
  if(ch(a[i]) < v) i++;
  for(k = l; k <= p; k++, j--)
    exch(a[k], a[j]);
  for(k = r; k >= q; k--, i++)
    exch(a[k], a[i]);

  quick_sort_3path(a, l, j, D);
  if((i == r) && (ch(a[i]) == v))
    i++;
  if(v != '\0')
    quick_sort_3path(a, j+1, i-1, D+1);
  quick_sort_3path(a, i, r, D);  
    
}


void radixLSD(Item a[], int l, int r){
  int i, j, w, count[R+1];
  //evert control word
  for(w = bytesword-1; w >= 0; w--){
    
    for(j = 0; j < R; j++)
      count[j] = 0;

    //控制字索引统计， 使用索引统计排序
    for(i = l; i <= r; i++)
      count[digit(a[i], w)+1]++;

    for(j = 1; j< R; j++)
      count[j] += count[j-1];

    for(i = l; i <= r; i++)
      aux[count[digit(a[i], w)]++] = a[i];
    
    for(i = l; i <= r; i++)
      a[i] = aux[i-1];
    
  }
}










int test_digit(int argc, char* argv[]){
    int a = 3716;
    int i;
    for(i = 0; i < 32; i++){
        int x = digit(a, i);
        printf("%d ", x);
    }
    printf("\n");
}
