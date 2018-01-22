#ifndef COMPLESSODOUBLE_H
#define COMPLESSODOUBLE_H

#include "complesso.h"
#include "complessoarithmeticexecutor.h"

#include <math.h>

class ComplessoDouble : public Complesso<double>
{
public:
    ComplessoDouble(const double,const double);

    ComplessoDouble operator +(const ComplessoDouble&)const;
    ComplessoDouble operator -(const ComplessoDouble&)const;
    ComplessoDouble operator *(const ComplessoDouble&)const;
    ComplessoDouble operator /(const ComplessoDouble&)const;

    // operazione propria di ComplessoDouble
    ComplessoDouble squareRoot()const;

    void printAll(){
        std::cout << "reale " << (this->getReale()) << " immaginaria" << (this->getImmaginaria()) << std::endl;
    }
};

#endif // COMPLESSODOUBLE_H
