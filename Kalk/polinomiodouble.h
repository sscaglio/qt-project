#ifndef POLINOMIODOUBLE_H
#define POLINOMIODOUBLE_H

#include "polinomio.h"
#include "polynomialarithmeticexecutor.h"

#include <cmath>
#include<QStringList>

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

    static PolinomioDouble parse(const QString&);
    static QString convertToQString(const PolinomioDouble&rht);
};

#endif // POLINOMIODOUBLE_H
