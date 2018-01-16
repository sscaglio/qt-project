#ifndef MATRICE
#define MATRICE

#include<limits>
#include<stdexcept>
#include<QVector>

#include "boundchecker.h"

using std::numeric_limits;
using std::domain_error;
using std::overflow_error;
using std::underflow_error;

template<typename T>
class Matrice{// eredita da classe astratta MatriceAstratta

    QVector<T> matrice;
    unsigned int righe;
    unsigned int colonne;

    static Boundchecker<T> bd;

public:
    Matrice(const unsigned int = 0,const unsigned int = 0);

    Matrice operator+(const Matrice&)const ;
    Matrice operator-(const Matrice&)const ;
    Matrice operator*(const Matrice&)const ;

    //test fn
    void insertValue(const T& val){
        matrice.push_back(val);
    }

    void printAll(){
        for(unsigned int i = 0 ; i < righe * colonne;++i){
            std::cout << matrice[i] << " ";
        }
    }
};

// campo dati statico per creare unica istanza boundchecker
template<typename T>
Boundchecker<T> Matrice<T>::bd = Boundchecker<T>(std::numeric_limits<T>::max(),(-1) * std::numeric_limits<T>::max());

// costruttore
template<typename T>
Matrice<T>::Matrice(const unsigned int r,const unsigned int c)
    :matrice(QVector<T>()),righe(r),colonne(c)
{}


// operatore somma tra tipi matrice
// testato errore dimensioni non compatibili
// controlla eventule condizione di memory leak in caso di
// somma inconsistente
template<typename T>
Matrice<T>
Matrice<T>::operator +(const Matrice<T>& rht) const{

    try{
        if(!(righe == rht.righe && colonne == rht.colonne)){
            throw domain_error("dimensione matrici non compatibili");
        }
        Matrice<T> res = Matrice<T>(righe,colonne);
        for(unsigned int i = 0 ;i < (righe * colonne);++i){
            T sommaElemento = T();
            bd.addConsistent(matrice[i],rht.matrice[i]);
            sommaElemento = matrice[i] + rht.matrice[i];
            res.matrice.push_back(sommaElemento);
        }
    return res;
    }
    catch(exception & e){
        std::cout << e.what() << std::endl;
    }
    return Matrice<T>();
}

#endif // MATRICE

