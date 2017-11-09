#ifndef NUMBER_FLOAT_H
#define NUMBER_FLOAT_H

//interface of Number type use float
//一个数据类型：
//    1 类型 (类型定义声明信息) 
//    2 类型上的操作。
//一个接口 就是声明整个数据类型的文件，任何引用了接口文件的C文件都能够使用该数据类型（当然要包括类型的操作）

typedef float Number;
Number randNum();
#endif
