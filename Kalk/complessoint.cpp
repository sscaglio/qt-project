#include "complessoint.h"

ComplessoInt::ComplessoInt(const int reale,const int immaginaria)
    :Complesso(reale,immaginaria)
{}

ComplessoInt
ComplessoInt::operator +(const ComplessoInt& rht) const{
    return ComplessoArithmeticExecutor<ComplessoInt,int>::add(*this,rht);
}

ComplessoInt
ComplessoInt::operator -(const ComplessoInt& rht)const{
    return ComplessoArithmeticExecutor<ComplessoInt,int>::sub(*this,rht);
}

ComplessoInt
ComplessoInt::operator *(const ComplessoInt& rht)const{
    return ComplessoArithmeticExecutor<ComplessoInt,int>::mul(*this,rht);
}

ComplessoInt
ComplessoInt::operator /(const ComplessoInt& rht)const{
    return ComplessoArithmeticExecutor<ComplessoInt,int>::div(*this,rht);
}

ComplessoInt
ComplessoInt::factorial()const{
    int factorialReale = this->getReale();
    int factorialImmaginaria = this->getImmaginaria();
    int daMoltReale = factorialReale - 1;
    int daMoltImmaginaria = factorialImmaginaria - 1;
    while(daMoltReale > 1){
        getBoundChecker().mulConsistent(factorialReale,daMoltReale);
        factorialReale*=daMoltReale;
        --daMoltReale;
    }
    // nessun overflow underflow in operazione di fattoriale per parte reale
    while(daMoltImmaginaria > 1){
        getBoundChecker().mulConsistent(factorialImmaginaria,daMoltImmaginaria);
        factorialImmaginaria*=daMoltImmaginaria;
        --daMoltImmaginaria;
    }

    // nessun overflow underflow in operazione di fattoriale per parte immaginaria
    return ComplessoInt(factorialReale,factorialImmaginaria);

}

ComplessoInt
ComplessoInt::parse(const QString & toBeParsed){
    QStringList res = toBeParsed.split(",",QString::SkipEmptyParts);
    QString immaginaria = res.at(1);
    return ComplessoInt(res.at(0).toInt(),immaginaria.remove('i').toInt());
}

QString
ComplessoInt::convertToQString(const ComplessoInt& toBeConverted){
    QString res = QString::number(toBeConverted.reale) + " ," + QString::number(toBeConverted.immaginaria) + "i";
    return res;
}
