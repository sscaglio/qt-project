#ifndef COMPLESSOINT_H
#define COMPLESSOINT_H

#include "complesso.h"
#include "complessoarithmeticexecutor.h"

#include<QString>
#include<QStringList>

class ComplessoInt : public Complesso<int>
{
    friend class ComplessoArithmeticExecutor<ComplessoInt,int>;
public:
    ComplessoInt(const int = 0,const int = 0);

    ComplessoInt operator+(const ComplessoInt&)const;
    ComplessoInt operator-(const ComplessoInt&)const;
    ComplessoInt operator*(const ComplessoInt&)const;
    ComplessoInt operator/(const ComplessoInt&)const;

    // operazione propria di ComplessoInt
    ComplessoInt factorial()const;

    static ComplessoInt parse(const QString &);
    static QString convertToQString(const ComplessoInt&);


};




#endif // COMPLESSOINT_H
