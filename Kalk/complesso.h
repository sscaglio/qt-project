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

    const T reale;
    const T immaginaria;

     static const Boundchecker<T>bd;

public :
    Complesso(const T& = 0,const T& = 0);

    Complesso operator+(const Complesso&)const;
    Complesso operator-(const Complesso&)const;
    Complesso operator*(const Complesso&)const;
    Complesso operator/(const Complesso&)const;

    T getReale()const;
    T getImmaginaria()const;
    Boundchecker<T> getBoundChecker()const;

    void printAll(){
        std::cout << "R: " << reale << std::endl;
        std::cout << "I: " << immaginaria << std::endl;
    }
};

//campo dati statico per singola istanza di boundchecker
template<typename T>
const Boundchecker<T> Complesso<T>::bd = Boundchecker<T>(std::numeric_limits<T>::max(),(-1) * std::numeric_limits<T>::max());

//costruttore
template<typename T>
Complesso<T>::Complesso(const T& r,const T& i)
    :reale(r),immaginaria(i){}


// operatore somma tra complessi
// testato correttezza operazione(nessun tentativo sollevamento eccezioni runtime)
template<typename T>
Complesso<T>
Complesso<T>::operator +(const Complesso<T>& rht)const{
    try{
        bd.addConsistent(reale,rht.reale);
        bd.addConsistent(immaginaria,rht.immaginaria);
        // entrambe operazioni di somma non causano overflow e underflow
        return Complesso(reale + rht.reale,immaginaria + rht.immaginaria);

    }
    catch(runtime_error& e){
        std::cout << e.what() << std::endl;
    }
    return 0;
}


// operazione differenza tra complessi
// testato correttezza operazione(nessun tentativo sollevamento eccezioni runtime)
template<typename T>
Complesso<T>
Complesso<T>::operator -(const Complesso<T>& rht) const{
    try{
        bd.subConsistent(reale,rht.reale);
        bd.subConsistent(immaginaria,rht.immaginaria);
        // entrambe operazioni di somma non causano overflow e underflow
        return Complesso(reale - rht.reale,immaginaria - rht.immaginaria);

    }
    catch(runtime_error& e){
        std::cout << e.what() << std::endl;
    }
    return 0;
}

// operazione prodotto tra complessi
// testato correttezza operazione(nessun tentativo sollevamento eccezioni runtime)
template<typename T>
Complesso<T>
Complesso<T>::operator *(const Complesso<T>& rht)const {
    try{
        // prodotto tra 2 complessi descritto da relazione
        // i parte immaginaria
        //(a + bi)*(c + di) = (ac - bd) + (bc + ad)i
        bd.mulConsistent(reale,rht.reale);
        T primoTermine = reale * rht.reale;
        bd.mulConsistent(immaginaria,rht.immaginaria);
        T secondoTermine = immaginaria * rht.immaginaria;
        // ac e bd consistenti
        bd.mulConsistent(immaginaria,rht.reale);
        T terzoTermine = immaginaria * rht.reale;
        bd.mulConsistent(reale,rht.immaginaria);
        T quartoTermine = reale * rht.immaginaria;
        // bc e ad consistenti
        bd.subConsistent(primoTermine,secondoTermine);
        // ac - bd consistente;
        bd.addConsistent(terzoTermine,quartoTermine);
        // bc + ad consistente

        // -> (ac - bd) - (bc + ad) consistente
        return Complesso(primoTermine - secondoTermine,terzoTermine + quartoTermine);
    }
    catch(runtime_error& e){
        std::cout << e.what() << std::endl;
    }
    return 0;
}


// operazione divisione tra complessi
// CORRETTEZZA DA TESTARE considera spezzare in piu' metodi
template<typename T>
Complesso<T>
Complesso<T>::operator /(const Complesso<T>& rht)const {
    try{
        // prodotto tra 2 complessi descritto da relazione
        // i parte immaginaria
        //(a + bi)/(c + di) = ((ac - bd)/(c*c + d*d))/((bc + ad)/(c*c + d*d))i
        bd.mulConsistent(reale,rht.reale);
        T primoTermine = reale * rht.reale;
        bd.mulConsistent(immaginaria,rht.immaginaria);
        T secondoTermine = immaginaria * rht.immaginaria;
        // ac e bd consistenti
        bd.mulConsistent(immaginaria,rht.reale);
        T terzoTermine = immaginaria * rht.reale;
        bd.mulConsistent(reale,rht.immaginaria);
        T quartoTermine = reale * rht.immaginaria;
        // bc e ad consistenti
        bd.addConsistent(primoTermine,secondoTermine);
        // ac + bd consistente;
        T primoNumeratore = primoTermine + secondoTermine;
        bd.subConsistent(terzoTermine,quartoTermine);
        // bc - ad consistente
        T secondoNumeratore = terzoTermine - quartoTermine;
        bd.mulConsistent(rht.reale,rht.reale);
        // c al quadrato consistente
        bd.mulConsistent(rht.immaginaria,rht.immaginaria);
        // d al quadrato consistente
        bd.addConsistent(rht.reale * rht.reale,rht.immaginaria * rht.immaginaria);
        // denominatore consistente
        T denominatore = rht.reale * rht.reale + rht.immaginaria * rht.immaginaria;
        bd.divConsistent(primoNumeratore,denominatore);
        // (ac + bd)/(c^2 + d^2) consistente
        T parteReale = primoNumeratore / denominatore;
        bd.divConsistent(secondoNumeratore,denominatore);
        // ->((bc - ad)/(c^2 + d^2)) consistente
        T parteImmaginaria = secondoNumeratore / denominatore;
        // tutte le operazioni che compongono il risultante complesso sono
        // consistenti -> complesso tornato e' consistente
        return Complesso(parteReale,parteImmaginaria);
    }
    catch(runtime_error& e){
        std::cout << e.what() << std::endl;
    }
    return 0;
}

template<typename T>
T
Complesso<T>::getReale() const{
    return reale;
}

template<typename T>
T
Complesso<T>::getImmaginaria()const{
    return immaginaria;
}

template<typename T>
Boundchecker<T>
Complesso<T>::getBoundChecker()const{
    return bd;
}

#endif // COMPLESSO

