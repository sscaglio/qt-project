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
    bool polinomioNullo()const;

};


template<typename T>
const Boundchecker<T> Polinomio<T>::bd = Boundchecker<T>(numeric_limits<T>::max(),(-1) * numeric_limits<T>::max());

template<typename T>
Polinomio<T>::Polinomio(){}

template<typename T>
bool
Polinomio<T>::polinomioNullo()const{
    return pol.empty();
}

#endif // POLINOMIO

