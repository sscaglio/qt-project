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


ComplessoDouble
ComplessoDouble::parse(const QString & toBeParsed){
    QStringList res = toBeParsed.split(",",QString::SkipEmptyParts);
    QString immaginaria = res.at(1);
    return ComplessoDouble(res.at(0).toDouble(),immaginaria.remove('i').toDouble());
}

QString
ComplessoDouble::convertToQString(const ComplessoDouble & toBeConverted){
    QString res = QString::number(toBeConverted.reale) + " , " + QString::number(toBeConverted.immaginaria) + "i";
    return res;
}
