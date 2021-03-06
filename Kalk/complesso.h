#ifndef COMPLESSO
#define COMPLESSO

#include<iostream>
#include<limits>
#include<stdexcept>

#include "boundchecker.h"

using std::bad_alloc;
using std::numeric_limits;
using std::overflow_error;
using std::underflow_error;

using std::cout;
using std::endl;

template<typename T>
class Complesso{

protected:
    T reale;
    T immaginaria;

    static Boundchecker<T> bd;

public :
    Complesso(const T& = 0,const T& = 0);


};

//costruttore
template<typename T>
Complesso<T>::Complesso(const T& r,const T& i)
    :reale(r),immaginaria(i){}

// campo dati statico per creare unica istanza boundchecker
template<typename T>
Boundchecker<T> Complesso<T>::bd = Boundchecker<T>(std::numeric_limits<T>::max(),(-1) * std::numeric_limits<T>::max());



#endif // COMPLESSO

