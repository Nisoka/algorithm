#ifndef REGION_BIT_H
#define REGION_BIT_H

/*
10.1 位、字节、字.
    位、字节、字 是最基本的位作为基数域的实现.
    可以扩展抽象 位、字节、字
    字 代表 关键字的长度.
    位 代表 关键字最小可以进行比较的单位
    字节 对于确定问题 应该选择的最小进行比较的长度,
        例如字符串 就应该选择字符, 对于整数 就应该选择2^n个位.

*/

//关键字的最小单位长度, 这三个都应该扩展到需要的情况.
#define bitsword 32
//控制字内最小单位长度.
#define bitsbyte 8
//关键字 内 控制字 个数.
#define bytesword 4
//R-1 就是 00000000000000000000000011111111 最低字节掩码
// 用来获得控制字.
#define R (1 << bitsbyte)

//取A 的第B个字节 (获得第B个控制字)
#define digit(A, B) ((A) >> (bitsword - ((B)+1)*bitsbyte) & (R-1))
//#define digit(A, B) A[B]


#endif // REGION_BIT_H
