#include "polinomiodouble.h"

PolinomioDouble::PolinomioDouble()
{}

PolinomioDouble
PolinomioDouble::operator +(const PolinomioDouble& rht)const{
    return PolynomialArithmeticExecutor<PolinomioDouble,double>::add(*this,rht);
}

PolinomioDouble
PolinomioDouble::operator -(const PolinomioDouble& rht)const{
    return PolynomialArithmeticExecutor<PolinomioDouble,double>::sub(*this,rht);
}

PolinomioDouble
PolinomioDouble::operator *(const PolinomioDouble& rht)const{
    return PolynomialArithmeticExecutor<PolinomioDouble,double>::mul(*this,rht);
}


PolinomioDouble
PolinomioDouble::squareRoot()const{
    PolinomioDouble res = PolinomioDouble();
    for(int i = 0 ; i < pol.size();++i){
        res.pol.append(Monomio<double>(sqrt(pol[i].getCoefficiente()),sqrt(pol[i].getGrado())));
    }
    return res;
}


PolinomioDouble
PolinomioDouble::parse(const QString & rht){
    QStringList res = rht.split(",",QString::SkipEmptyParts);
    PolinomioDouble val = PolinomioDouble();
    for(int i= 0 ; i < res.size();++i){
        if(res[i] != "s"){// se res[i] = 's' -> salta inserimento simbolo
            if(res[i].contains("x^")){// esiste grado
                QStringList tmp = res[i].split("x^",QString::SkipEmptyParts);
                if(tmp.size() == 2){
                val.pol.append(Monomio<double>(tmp.at(0).toInt(),(tmp.at(1)).toInt()));
                }
                else{
                    val.pol.append(Monomio<double>(1,tmp.at(0).toInt()));
                }
            }
            else{// non esiste grado

                val.pol.append(Monomio<double>(res[i].toInt(),0));
            }
        }
    }
    std::sort(val.pol.begin(),val.pol.end());
    return val;
}

QString
PolinomioDouble::convertToQString(const PolinomioDouble & rht){
    QString res = QString();
    int i = 0;
    for(; i < (rht.pol.size() - 1);++i){
        double coeff = rht.pol[i].getCoefficiente();
        int grad = rht.pol[i].getGrado();
        if(coeff != 0){
            res+=(QString::number(coeff));
        }
        if(grad != 0){
            res+=("x^" + QString::number(grad));
        }
        res+=",";
    }
    double coeff= rht.pol[i].getCoefficiente();
    int grad = rht.pol[i].getGrado();
    if(coeff != 0){
        res+=(QString::number(coeff));
    }
    if(grad != 0){
        res+=("x^" + QString::number(grad));
    }
    return res;
}
