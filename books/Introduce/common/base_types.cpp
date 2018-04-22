#include "base_types.h"

nint::nint(int i)
{
    val = i;
}

void nint::SetRandom()
{
    val = random_int();
}

bool nint::operator >(nint obj)
{
    if(val > obj.GetValue())
        return true;
}


void nint::Print()
{
    printf("%d", val);
}

