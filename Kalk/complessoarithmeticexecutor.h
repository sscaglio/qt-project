#ifndef COMPLESSOARITHMETICEXECUTOR
#define COMPLESSOARITHMETICEXECUTOR

// classe templatizzata statica
// implementa aritmetica della classe complesso
// indipendentemente dal tipo effettivo(intero o double)
// T tipo di calcolo
// U tipo coefficiente tipo di calcolo

#include"boundchecker.h"

template<typename T,typename U>
class ComplessoArithmeticExecutor{

    static const Boundchecker<U> bd;
public:
    static T add(const T&,const T&);
    static T sub(const T&,const T&);
    static T mul(const T&,const T&);
    static T div(const T&,const T&);
};

template<typename T,typename U>
const Boundchecker<U>
ComplessoArithmeticExecutor<T,U>::bd =
           Boundchecker<U>(std::numeric_limits<U>::max(),(-1) * std::numeric_limits<U>::max());

template<typename T,typename U>
T
ComplessoArithmeticExecutor<T,U>::add(const T& lht,const T& rht){
    try{
        bd.addConsistent(lht.getReale(),rht.getReale());
        bd.addConsistent(lht.getImmaginaria(),rht.getImmaginaria());
        // entrambe operazioni di somma non causano overflow e underflow
        return T(lht.getReale() + rht.getReale(),lht.getImmaginaria() + rht.getImmaginaria());

    }
    catch(runtime_error& e){
        std::cout << e.what() << std::endl;
    }
    return T(0,0);
}

template<typename T,typename U>
T
ComplessoArithmeticExecutor<T,U>::sub(const T& lht,const T&rht){
    try{
        bd.subConsistent(lht.getReale(),rht.getReale());
        bd.subConsistent(lht.getImmaginaria(),rht.getImmaginaria());
        // entrambe operazioni di somma non causano overflow e underflow
        return T(lht.getReale() - rht.getReale(),lht.getImmaginaria() - rht.getImmaginaria());

    }
    catch(runtime_error& e){
        std::cout << e.what() << std::endl;
    }
    return T(0,0);
}

template<typename T,typename U>
T
ComplessoArithmeticExecutor<T,U>::mul(const T& lht,const T& rht){
    try{
        // prodotto tra 2 complessi descritto da relazione
        // i parte getImmaginaria()
        //(a + bi)*(c + di) = (ac - bd) + (bc + ad)i
        bd.mulConsistent(lht.getReale(),rht.getReale());
        U primoTermine = lht.getReale() * rht.getReale();
        bd.mulConsistent(lht.getImmaginaria(),rht.getImmaginaria());
        U secondoTermine = lht.getImmaginaria() * rht.getImmaginaria();
        // ac e bd consistenti
        bd.mulConsistent(lht.getImmaginaria(),rht.getReale());
        U terzoTermine = lht.getImmaginaria() * rht.getReale();
        bd.mulConsistent(lht.getReale(),rht.getImmaginaria());
        U quartoTermine = lht.getReale() * rht.getImmaginaria();
        // bc e ad consistenti
        bd.subConsistent(primoTermine,secondoTermine);
        // ac - bd consistente;
        bd.addConsistent(terzoTermine,quartoTermine);
        // bc + ad consistente

        // -> (ac - bd) - (bc + ad) consistente
        return T(primoTermine - secondoTermine,terzoTermine + quartoTermine);
    }
    catch(runtime_error& e){
        std::cout << e.what() << std::endl;
    }
    return T(0,0);
}


template<typename T,typename U>
T
ComplessoArithmeticExecutor<T,U>::div(const T& lht,const T& rht){
    try{
        // prodotto tra 2 complessi descritto da relazione
        // i parte immaginaria
        //(a + bi)/(c + di) = ((ac - bd)/(c*c + d*d))/((bc + ad)/(c*c + d*d))i
        bd.mulConsistent(lht.getReale(),rht.getReale());
        U primoTermine = lht.getReale() * rht.getReale();
        bd.mulConsistent(lht.getImmaginaria(),rht.getImmaginaria());
        U secondoTermine = lht.getImmaginaria() * rht.getImmaginaria();
        // ac e bd consistenti
        bd.mulConsistent(lht.getImmaginaria(),rht.getReale());
        U terzoTermine = lht.getImmaginaria() * rht.getReale();
        bd.mulConsistent(lht.getReale(),rht.getImmaginaria());
        U quartoTermine = lht.getReale() * rht.getImmaginaria();
        // bc e ad consistenti
        bd.addConsistent(primoTermine,secondoTermine);
        // ac + bd consistente;
        U primoNumeratore = primoTermine + secondoTermine;
        bd.subConsistent(terzoTermine,quartoTermine);
        // bc - ad consistente
        U secondoNumeratore = terzoTermine - quartoTermine;
        bd.mulConsistent(rht.getReale(),rht.getReale());
        // c al quadrato consistente
        bd.mulConsistent(rht.getImmaginaria(),rht.getImmaginaria());
        // d al quadrato consistente
        bd.addConsistent(rht.getReale() * rht.getReale(),rht.getImmaginaria() * rht.getImmaginaria());
        // denominatore consistente
        U denominatore = rht.getReale() * rht.getReale() + rht.getImmaginaria() * rht.getImmaginaria();
        bd.divConsistent(primoNumeratore,denominatore);
        // (ac + bd)/(c^2 + d^2) consistente
        U parteReale = primoNumeratore / denominatore;
        bd.divConsistent(secondoNumeratore,denominatore);
        // ->((bc - ad)/(c^2 + d^2)) consistente
        U parteImmaginaria = secondoNumeratore / denominatore;
        // tutte le operazioni che compongono il risultante complesso sono
        // consistenti -> complesso tornato e' consistente
        return T(parteReale,parteImmaginaria);
    }
    catch(runtime_error& e){
        std::cout << e.what() << std::endl;
    }
    return T(0,0);
}


#endif // COMPLESSOARITHMETICEXECUTOR

