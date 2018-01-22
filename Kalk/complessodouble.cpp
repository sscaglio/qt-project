#include "complessodouble.h"

ComplessoDouble::ComplessoDouble(const double reale,const double immaginaria)
    :Complesso(reale,immaginaria)
{}

ComplessoDouble
ComplessoDouble::operator +(const ComplessoDouble& rht) const{
    return ComplessoArithmeticExecutor<ComplessoDouble,double>::add(*this,rht);
}

ComplessoDouble
ComplessoDouble::operator -(const ComplessoDouble& rht)const{
    return ComplessoArithmeticExecutor<ComplessoDouble,double>::sub(*this,rht);
}

ComplessoDouble
ComplessoDouble::operator *(const ComplessoDouble& rht)const{
    return ComplessoArithmeticExecutor<ComplessoDouble,double>::mul(*this,rht);
}

ComplessoDouble
ComplessoDouble::operator /(const ComplessoDouble& rht)const{
    return ComplessoArithmeticExecutor<ComplessoDouble,double>::div(*this,rht);
}


ComplessoDouble
ComplessoDouble::squareRoot()const{
    return ComplessoDouble(sqrt(getReale()),sqrt(getImmaginaria()));
}
