#ifndef COMPLEX_H
#define COMPLEX_H

/*
 ADT
    是只抽象暴露出接口 不允许用户操作内部数据项
一级ADT(抽象!数据类型)
    不仅抽象暴露接口, 并且暴露ADT的类型声明 类型指针, 但是不暴露内部数据项, 所以外部客户程序可以定义ADT的变量
    可以赋值 复制 传参, 但是没有得到ADT的内部数据项, 所以不能直接使用内部数据结构项.

一级数据类型
    则完全暴露 直接 暴露 类型定义, 内部数据项也被直接暴露
*/

// 复数的一级ADT 或者 一级数据类型
#define COMPLEX_ADT
#define COMPLEX_DATATYPE

#ifdef COMPLEX_ADT
// struct complex 定义在.c中, .h暴露出的 只是类型声明, 外部客户可以声明Complex变量 但不知道具体成员 不可访问.
typedef struct complex *Complex_pointer;

Complex_pointer complex_init(float, float);
float Re(Complex_pointer);
float Im(Complex_pointer);
Complex_pointer complex_mult(Complex_pointer, Complex_pointer);
#else
//如此在.h 中进行struct定义 直接暴露内部结构数据项, 外部客户可访问.
typedef struct{
    float Re;
    float Im;
}Complex;

Complex complex_init(float, float);
float Re(Complex);
float Im(Complex);
Complex complex_mult(Complex, Complex);

#endif


#endif // COMPLEX_H
