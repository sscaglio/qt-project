#ifndef COMPLESSOINT_H
#define COMPLESSOINT_H

#include "complesso.h"
#include "complessoarithmeticexecutor.h"

class ComplessoInt : public Complesso<int>
{
public:
    ComplessoInt(const int,const int);

    ComplessoInt operator+(const ComplessoInt&)const;
    ComplessoInt operator-(const ComplessoInt&)const;
    ComplessoInt operator*(const ComplessoInt&)const;
    ComplessoInt operator/(const ComplessoInt&)const;

    // operazione propria di ComplessoInt
    ComplessoInt factorial()const;

    void printAll(){
        std::cout << "reale " << (this->getReale()) << " immaginaria" << (this->getImmaginaria()) << std::endl;
    }
};




#endif // COMPLESSOINT_H
