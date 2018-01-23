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

void
PolinomioDouble::printAll()const{
    for(int i = 0 ; i < pol.size();++i){
        pol[i].printAll();
    }
}

void
PolinomioDouble::testOperation()const{
    PolinomioDouble res = PolinomioDouble();
    PolinomioDouble p1 = PolinomioDouble();
    PolinomioDouble p2 = PolinomioDouble();
    for(int i = 4; i > 0;--i){
        p1.pol.append(Monomio<double>(i * 0.5,i));
        p2.pol.append(Monomio<double>(i * 0.5,i));
    }


    std::cout << "PRIMO POLINOMIO " << std::endl;
    p1.printAll();

    std::cout<< "SECONDO POLINOMIO" << std::endl;
    p2.printAll();

    cout << "TEST OP ARITHMETIC" << std::endl;
    cout << "+" << std::endl;
    (p1 + p2).printAll();
    cout << std::endl;
    cout << std::endl;
    cout << "-" << std::endl;
    (p1 - p2).printAll();
    cout << std::endl;
    cout << std::endl;
    cout << "*" << std::endl;
    (p1 * p2).printAll();
    cout << std::endl;
    cout << std::endl;
    cout << "RISULTATO PRODOTTO" << std::endl;
    p1.squareRoot().printAll();
    cout << std::endl;
}

