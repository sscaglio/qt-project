#ifndef POLINOMIO
#define POLINOMIO

#include<algorithm>
#include<iostream>
#include<QList>
#include<limits>
#include<stdexcept>

#include "boundchecker.h"
#include "monomio.h"

using std::bad_alloc;
using std::cout;
using std::numeric_limits;

template<typename T>
class Polinomio{

protected:
    QList<Monomio<T> > pol;

    static const Boundchecker<T> bd;

public :

    Polinomio();

    void testOperation()const;
    void printAll()const;
};


template<typename T>
const Boundchecker<T> Polinomio<T>::bd = Boundchecker<T>(numeric_limits<T>::max(),(-1) * numeric_limits<T>::max());

template<typename T>
Polinomio<T>::Polinomio(){}


template<typename T>
void
Polinomio<T>::printAll()const{
    for(int i = 0 ; i < pol.size();++i){
        pol[i].printAll();
    }
}

template<typename T>
void
Polinomio<T>::testOperation()const{
    Polinomio<T> res = Polinomio<T>();
    Polinomio<T> p1 = Polinomio<T>();
    Polinomio<T> p2 = Polinomio<T>();
    for(int i = 2; i > 0;--i){
        p1.pol.append(Monomio<T>(i,i));
        p2.pol.append(Monomio<T>(i,i));
    }


    std::cout << "PRIMO POLINOMIO " << std::endl;
    p1.printAll();

    std::cout<< "SECONDO POLINOMIO" << std::endl;
    p2.printAll();


    res = p1 * p2;
    std::cout << "RISULTATO PRODOTTO" << std::endl;
    res.printAll();
    cout << std::endl;
}

#endif // POLINOMIO

