#include "polinomioint.h"

PolinomioInt::PolinomioInt()
{}

PolinomioInt
PolinomioInt::operator +(const PolinomioInt& rht)const{
    return PolynomialArithmeticExecutor<PolinomioInt,int>::add(*this,rht);
}

PolinomioInt
PolinomioInt::operator -(const PolinomioInt& rht)const{
    return PolynomialArithmeticExecutor<PolinomioInt,int>::sub(*this,rht);
}

PolinomioInt
PolinomioInt::operator *(const PolinomioInt& rht)const{
    return PolynomialArithmeticExecutor<PolinomioInt,int>::mul(*this,rht);
}

PolinomioInt
PolinomioInt::factorial()const{
    PolinomioInt res = PolinomioInt();
    for(int i = 0 ; i < pol.size();++i){
        int coeffFactorial = pol[i].getCoefficiente();
        int daMoltCoeff = coeffFactorial - 1;
        while(daMoltCoeff > 1){
            bd.mulConsistent(coeffFactorial,daMoltCoeff);
            coeffFactorial*=daMoltCoeff;
            --daMoltCoeff;
        }
        int gradoFactorial = pol[i].getGrado();
        int daMoltGrado = gradoFactorial - 1;
        while(daMoltGrado > 1){
            bd.mulConsistent(gradoFactorial,daMoltGrado);
            gradoFactorial*=daMoltGrado;
            --daMoltGrado;
        }
        res.pol.append(Monomio<int>(coeffFactorial,gradoFactorial));
    }
    return res;
}

void
PolinomioInt::printAll()const{
    for(int i = 0 ; i < pol.size();++i){
        pol[i].printAll();
    }
}

void
PolinomioInt::testOperation()const{
    PolinomioInt res = PolinomioInt();
    PolinomioInt p1 = PolinomioInt();
    PolinomioInt p2 = PolinomioInt();
    for(int i = 4; i > 0;--i){
        p1.pol.append(Monomio<int>(i,i));
        p2.pol.append(Monomio<int>(i,i));
    }


    std::cout << "PRIMO POLINOMIO " << std::endl;
    p1.printAll();

    std::cout<< "SECONDO POLINOMIO" << std::endl;
    p2.printAll();


    res = p1.factorial();// * p2;
    std::cout << "RISULTATO PRODOTTO" << std::endl;
    res.printAll();
    cout << std::endl;
}


PolinomioInt
PolinomioInt::parse(const QString& rht){

    QStringList res = rht.split(",",QString::SkipEmptyParts);
    PolinomioInt val = PolinomioInt();
    for(int i= 0 ; i < res.size();++i){
        if(res[i] != "s"){// se res[i] = 's' -> salta inserimento simbolo
            QStringList par = res[i].split("x^");
            val.pol.append(Monomio<int>(par.at(0).toInt(),par.at(1).toInt()));
        }
    }
    return val;
}

QString
PolinomioInt::convertToQString(const PolinomioInt & rht){
    QString res = QString();
    unsigned int i = 0;
    for(; i < rht.pol.size();++i){
        res +=(QString::number(rht.pol[i].getCoefficiente()) + "x^" + QString::number(rht.pol[i].getGrado()) + ",");
    }
    res+=(QString::number(rht.pol[i].getCoefficiente()) + "x^" +QString::number(rht.pol[i].getGrado()));
    return res;
}
