#ifndef BASE_TYPES_H
#define BASE_TYPES_H

#include "common.h"

class nint
{
public:
    nint(){val = 0;}
    nint(int i);

    int GetValue(){return val;}
    void SetValue(int value){val = value;}
    void SetRandom();

    bool operator >(nint obj);


    void Print();
private:
    int val;
};



#endif // BASE_TYPES_H
