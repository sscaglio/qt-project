#ifndef POLINOMIODOUBLE_H
#define POLINOMIODOUBLE_H

#include "polinomio.h"
#include "polynomialarithmeticexecutor.h"

#include <cmath>

class PolinomioDouble : public Polinomio<double>
{
    friend class PolynomialArithmeticExecutor<PolinomioDouble,double>;
public:
    PolinomioDouble();

    PolinomioDouble operator+(const PolinomioDouble&)const;
    PolinomioDouble operator-(const PolinomioDouble&)const;
    PolinomioDouble operator*(const PolinomioDouble&)const;

    PolinomioDouble squareRoot()const;

    void printAll()const;

    void testOperation()const;
};

#endif // POLINOMIODOUBLE_H
