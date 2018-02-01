#ifndef COMPLESSODOUBLE_H
#define COMPLESSODOUBLE_H

#include "complesso.h"
#include "complessoarithmeticexecutor.h"

#include <math.h>

#include<QString>
#include<QStringList>

class ComplessoDouble : public Complesso<double>
{
    friend class ComplessoArithmeticExecutor<ComplessoDouble,double>;
public:
    ComplessoDouble(const double = 0,const double = 0);

    ComplessoDouble operator +(const ComplessoDouble&)const;
    ComplessoDouble operator -(const ComplessoDouble&)const;
    ComplessoDouble operator *(const ComplessoDouble&)const;
    ComplessoDouble operator /(const ComplessoDouble&)const;

    // operazione propria di ComplessoDouble
    ComplessoDouble squareRoot()const;

    static ComplessoDouble parse(const QString &);
    static QString convertToQString(const ComplessoDouble&);
};

#endif // COMPLESSODOUBLE_H
