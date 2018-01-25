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
