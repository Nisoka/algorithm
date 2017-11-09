#ifndef REGION_BYTE_H
#define REGION_BYTE_H

//取字符串A的第B个字符
#define digit(A, B) A[(B)]
/*
 digit(A, B) 是一个接口, 对于不同的数据, 需要使用不同的域, 来划分桶.

 例如
 对于int数据, 直接按位进行2进制快排即可.
    那么digit(A, B) 就每次取A的第B个字节(更精细就使用位)即可.

 对于string字符串类型数据,  则需要对每个字节(字符)获取, 来划分桶.
    那么digit(A, B) 就需要每次 获取第B个字符
    但是字符串经常是 不固定长度的, 所以可能需要更复杂的实现digit(A, B)
*/

#endif // REGION_BYTE_H
