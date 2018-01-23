#ifndef POLYNOMIALARITHMETICEXECUTOR
#define POLYNOMIALARITHMETICEXECUTOR

#include "boundchecker.h"

template<typename T,typename U>
class PolynomialArithmeticExecutor{

    static const Boundchecker<U> bd;

public :

    static T add(const T&,const T&);
    static T sub(const T&,const T&);
    static T mul(const T&,const T&);
};

template<typename T,typename U>
const Boundchecker<U>
PolynomialArithmeticExecutor<T,U>::bd =
        Boundchecker<U>(std::numeric_limits<U>::max(),(-1) * std::numeric_limits<U>::max());

template<typename T,typename U>
T
PolynomialArithmeticExecutor<T,U>::add(const T& lht,const T& rht){
    int i = 0;
    int j = 0;
    T res = T();
    try{
        while(i < lht.pol.size() && j < rht.pol.size()){
            if(lht.pol[i].getGrado() == rht.pol[j].getGrado()){
                // gradi monomi uguali -> possibile somma
                bd.addConsistent(lht.pol[i].getCoefficiente(),rht.pol[j].getCoefficiente());
                //somma consistente tra due monomi
                U coefficienteRisultante =
                        lht.pol[i].getCoefficiente() + rht.pol[j].getCoefficiente();
                if(coefficienteRisultante != 0){
                    res.pol.append(Monomio<U>(coefficienteRisultante,lht.pol[i].getGrado()));
                }
                ++i;
                ++j;
            }
            else{
                // gradi monomi distinti - > non possibile somma
                if(lht.pol[i].getGrado() > rht.pol[j].getGrado()){
                    // grado primo monomio maggiore del secondo
                    res.pol.append(lht.pol[i]);
                    ++i;
                }
                else{
                    // grado del secondo monomio maggiore del primo
                    res.pol.append(rht.pol[j]);
                    ++j;
                }
            }
        }
        T rimanente = T();
        if(i < lht.pol.size()){
            // esistono elementi rimanenti nel polinomio sx
            rimanente.pol = lht.pol.mid(i);
        }
        if(j < rht.pol.size()){
            // esistono elementi rimanenti nel polinomio dx
            rimanente.pol = rht.pol.mid(j);
        }
        if(!(rimanente.pol.empty())){
            // se polinomio rimanente non e' vuoto -> appendi al termine di res
            res.pol.append(rimanente.pol);
        }
        return res;
    }catch(runtime_error& e){
        std::cout << e.what() << std::endl;
    }
    return T();
}


template<typename T,typename U>
T
PolynomialArithmeticExecutor<T,U>::sub(const T& lht,const T& rht){

    int i = 0;
    int j = 0;
    T res = T();
    try{
        while(i < lht.pol.size() && j < rht.pol.size()){
            if(lht.pol[i].getGrado() == rht.pol[j].getGrado()){
                // gradi monomi uguali -> possibile differenza
                bd.subConsistent(lht.pol[i].getCoefficiente(),rht.pol[j].getCoefficiente());
                //sottrazione consistente tra due monomi
                U coefficienteRisultante =
                        lht.pol[i].getCoefficiente() - rht.pol[j].getCoefficiente();
                if(coefficienteRisultante != 0){
                    res.pol.append(Monomio<U>(coefficienteRisultante,lht.pol[i].getGrado()));
                }
                ++i;
                ++j;
            }
            else{
                // gradi monomi distinti - > non possibile differenza
                if(lht.pol[i].getGrado() > rht.pol[j].getGrado()){
                    // grado primo monomio maggiore del secondo
                    res.pol.append(lht.pol[i]);
                    ++i;
                }
                else{
                    // grado del secondo monomio maggiore del primo
                    // appendo negazione (poiche' operando destro di negazione)
                    // a risultato
                    res.pol.append(Monomio<U>((-1) * rht.pol[j].getCoefficiente(),rht.pol[j].getGrado()));
                    ++j;
                }
            }
        }
        T rimanente = T();
        if(i < lht.pol.size()){
            // esistono elementi rimanenti nel polinomio sx
            rimanente.pol = lht.pol.mid(i);
        }
        if(j < rht.pol.size()){
            // esistono elementi rimanenti nel polinomio dx
            rimanente.pol = rht.pol.mid(j);
            for(int i = 0 ; i < rimanente.pol.size();++i){
                rimanente.pol[i] =
                        Monomio<U>((-1) * rimanente.pol[i].getCoefficiente(),rimanente.pol[i].getGrado());
            }
        }
        if(!(rimanente.pol.empty())){
            // se polinomio rimanente non e' vuoto -> appendi al termine di res
            res.pol.append(rimanente.pol);
        }
        return res;
    }catch(runtime_error& e){
        std::cout << e.what() << std::endl;
    }
    return T();
}
#endif // POLYNOMIALARITHMETICEXECUTOR

