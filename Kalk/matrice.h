#ifndef MATRICE
#define MATRICE

#include<iostream>
#include<limits>
#include<stdexcept>
#include<QVector>

#include "boundchecker.h"

using std::bad_alloc;
using std::domain_error;
using std::logic_error;
using std::numeric_limits;
using std::overflow_error;
using std::underflow_error;

template<typename T>
class Matrice{// eredita da classe astratta MatriceAstratta

protected:
    QVector<T> matrice;
    unsigned int righe;
    unsigned int colonne;

    static Boundchecker<T> bd;

public:
    Matrice(const unsigned int = 0,const unsigned int = 0);

};

// campo dati statico per creare unica istanza boundchecker
template<typename T>
Boundchecker<T> Matrice<T>::bd = Boundchecker<T>(std::numeric_limits<T>::max(),(-1) * std::numeric_limits<T>::max());

// costruttore
template<typename T>
Matrice<T>::Matrice(const unsigned int r,const unsigned int c)
    :matrice(QVector<T>()),righe(r),colonne(c)
{}


#endif // MATRICE

