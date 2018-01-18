#ifndef MONOMIO
#define MONOMIO

#include<iostream>
#include<limits>
#include<stdexcept>

#include "boundchecker.h"

using std::cout;
using std::endl;
using std::numeric_limits;
using std::ostream;
using std::overflow_error;
using std::underflow_error;


template<typename T>
class Monomio{
    const T coefficiente;
    const unsigned int grado;

    static const Boundchecker<T> bd;

public:

    Monomio(const T = T(),const unsigned int = 0);

    Monomio operator+(const Monomio&) const;
    Monomio operator-(const Monomio&) const;
    Monomio operator*(const Monomio&) const;
    Monomio operator/(const Monomio&) const;

    bool operator>(const Monomio&)const;
    bool operator==(const Monomio&)const;
    bool operator>=(const Monomio&)const;

    void printAll(){
        cout << "coeff " << coefficiente << endl;
        cout << "grado " << grado << endl;
    }
};

// istanza boundchecker necessaria per controlli consistenza tra monomi
template<typename T>
const Boundchecker<T> Monomio<T>::bd = Boundchecker<T>(numeric_limits<T>::max(),(-1) * numeric_limits<T>::max());

template<typename T>
Monomio<T>::Monomio(const T c,const unsigned int g)
    : coefficiente(c),grado(g)
{}

template<typename T>
Monomio<T>
Monomio<T>::operator +(const Monomio<T>& rht)const{
    try{
        bd.addConsistent(coefficiente,rht.coefficiente);
        // somma consistente tra coefficienti sx e dx
        T coefficienteRisultante = coefficiente + rht.coefficiente;
        return Monomio<T>(coefficienteRisultante,grado);
    }catch(runtime_error & e){
        std::cout << e.what() << std::endl;
    }
    return Monomio<T>();
}

template<typename T>
Monomio<T>
Monomio<T>::operator -(const Monomio<T>& rht) const{
    try{
        bd.subConsistent(coefficiente,rht.coefficiente);
        // differenza consistente tra coefficienti sx e dx
        T coefficienteRisultante = coefficiente - rht.coefficiente;
        return Monomio<T>(coefficienteRisultante,grado);
    }catch(runtime_error & e){
        std::cout << e.what() << std::endl;
    }
    return Monomio<T>();
}

template<typename T>
Monomio<T>
Monomio<T>::operator *(const Monomio<T>& rht) const{
    try{
        bd.mulConsistent(coefficiente,rht.coefficiente);
        // prodotto consistente tra coefficienti sx e dx
        T coefficienteRisultante = coefficiente * rht.coefficiente;

        bd.addConsistent(grado,rht.grado);
        // somma gradi consistente tra monomio sx e dx
        unsigned int gradoRisultante = grado + rht.grado;
        return Monomio<T>(coefficienteRisultante,gradoRisultante);
    }catch(runtime_error & e){
        std::cout << e.what() << std::endl;
    }
    return Monomio<T>();
}

template<typename T>
Monomio<T>
Monomio<T>::operator /(const Monomio<T> & rht)const{
    // coefficiente sx e dx qualsiasi
    try{
        bd.divConsistent(coefficiente,rht.coefficiente);
        // divisione consistente tra coefficienti sx e dx
        T coefficienteRisultante = coefficiente / rht.coefficiente;
        bd.subConsistent(grado,rht.grado);
        // differenza consistente tra grado monomio sx e dx
        unsigned int gradoRisultante = grado - rht.grado;
        return Monomio<T>(coefficienteRisultante,gradoRisultante);
    }catch(runtime_error& e){
        std::cout << e.what() << std::endl;
    }
    return Monomio<T>();
}

template<typename T>
bool
Monomio<T>::operator>(const Monomio<T>& rht)const {
  return grado > rht.grado ||
    (grado == rht.grado && coefficiente > rht.coefficiente);
}

template<typename T>
bool
Monomio<T>::operator ==(const Monomio& rht)const{
    return coefficiente == rht.coefficiente &&
            grado == rht.grado;
}

template<typename T>
bool
Monomio<T>::operator >=(const Monomio& rht)const{
    return (*this > rht) || (*this == rht);
}

#endif // MONOMIO

