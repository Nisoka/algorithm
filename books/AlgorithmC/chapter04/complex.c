#include "complex.h"



#ifdef COMPLEX_ADT
struct complex{
    float Re;
    float Im;
};

Complex_pointer complex_init(float Re, float Im)
{
    Complex_pointer t = malloc(sizeof(struct complex));
    t->Re = Re;
    t->Im = Im;
    return t;
}

float Re(Complex_pointer t){
    return t->Re;
}

float Im(Complex_pointer t){
    return t->Im;
}

Complex_pointer complex_mult(Complex_pointer a, Complex_pointer b){
    return complex_init(Re(a)*Re(b) - Im(a)*Im(b), Re(a)*Im(b) + Im(a)*Re(b));
}


#else

Complex complex_init(float Re, float Im)
{
    Complex t;
    t.Re = Re;
    t.Im = Im;
    return t;
}

float Re(Complex t){
    return t.Re;
}

float Im(Complex t){
    return t.Im;
}

Complex complex_mult(Complex a, Complex b){
    Complex t;
    t.Re = a.Re*b.Re - a.Im*b.Im;
    t.Im = a.Re*b.Im + a.Im*b.Re;
    return t;
}

#endif
