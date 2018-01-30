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

#include<QDebug>

PolinomioInt
PolinomioInt::parse(const QString& rht){

    QStringList res = rht.split(",",QString::SkipEmptyParts);
    PolinomioInt val = PolinomioInt();
    for(int i= 0 ; i < res.size();++i){
        if(res[i] != "s"){// se res[i] = 's' -> salta inserimento simbolo
            if(res[i].contains("x^")){// esiste grado
                QStringList tmp = res[i].split("x^",QString::SkipEmptyParts);
                if(tmp.size() == 2){
                val.pol.append(Monomio<int>(tmp.at(0).toInt(),(tmp.at(1)).toInt()));
                }
                else{
                    val.pol.append(Monomio<int>(1,tmp.at(0).toInt()));
                }
            }
            else{// non esiste grado

                val.pol.append(Monomio<int>(res[i].toInt(),0));
            }
        }
    }
    return val;
}

QString
PolinomioInt::convertToQString(const PolinomioInt & rht){
    QString res = QString();
    int i = 0;
    for(; i < (rht.pol.size() - 1);++i){
        int coeff = rht.pol[i].getCoefficiente();
        int grad = rht.pol[i].getGrado();
        if(coeff != 0){
            res+=(QString::number(coeff));
        }
        if(grad != 0){
            res+=("x^" + QString::number(grad));
        }
        res+=",";
    }
    int coeff = rht.pol[i].getCoefficiente();
    int grad = rht.pol[i].getGrado();
    if(coeff != 0){
        res+=(QString::number(coeff));
    }
    if(grad != 0){
        res+=("x^" + QString::number(grad));
    }
    return res;
}
