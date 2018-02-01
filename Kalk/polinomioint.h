#ifndef POLINOMIOINT_H
#define POLINOMIOINT_H

#include "polinomio.h"

#include "polynomialarithmeticexecutor.h"

#include <QStringList>
#include<QDebug>
#include<algorithm>

class PolinomioInt : public Polinomio<int>
{
    friend class PolynomialArithmeticExecutor<PolinomioInt,int>;
public:
    PolinomioInt();

    PolinomioInt operator+(const PolinomioInt&)const;
    PolinomioInt operator-(const PolinomioInt&)const;
    PolinomioInt operator*(const PolinomioInt&)const;

    PolinomioInt factorial()const;

    static PolinomioInt parse(const QString&);
    static QString convertToQString(const PolinomioInt&);
};

#endif // POLINOMIOINT_H
