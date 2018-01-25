#ifndef POLINOMIOINT_H
#define POLINOMIOINT_H

#include "polinomio.h"

#include "polynomialarithmeticexecutor.h"

class PolinomioInt : public Polinomio<int>
{
    friend class PolynomialArithmeticExecutor<PolinomioInt,int>;
public:
    PolinomioInt();

    PolinomioInt operator+(const PolinomioInt&)const;
    PolinomioInt operator-(const PolinomioInt&)const;
    PolinomioInt operator*(const PolinomioInt&)const;

    void testOperation()const;
    void printAll()const;

    PolinomioInt factorial()const;
};

#endif // POLINOMIOINT_H
