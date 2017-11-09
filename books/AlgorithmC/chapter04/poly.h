#ifndef POLY_H
#define POLY_H
#include <stdlib.h>
#include <stdio.h>

typedef struct poly* Poly;

Poly poly_term(int coeff, int exp);
Poly poly_add(Poly p, Poly q);
Poly poly_mul(Poly p, Poly q);
float poly_eval(Poly p, float x);


#endif // POLY_H
