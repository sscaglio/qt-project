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
    for(int i = 2; i > 0;--i){
        p1.pol.append(Monomio<int>(1 + i,i));
        p2.pol.append(Monomio<int>(i,i));
    }


    std::cout << "PRIMO POLINOMIO " << std::endl;
    p1.printAll();

    std::cout<< "SECONDO POLINOMIO" << std::endl;
    p2.printAll();


    res = p1 - p2;
    std::cout << "RISULTATO PRODOTTO" << std::endl;
    res.printAll();
    cout << std::endl;
}
