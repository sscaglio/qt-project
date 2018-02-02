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
    static T reduxEqual(T&);
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
        throw e;
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
        throw e;
    }
    return T();
}

template<typename T,typename U>
T
PolynomialArithmeticExecutor<T,U>::mul(const T& lht,const T& rht){

    try{
        T bufferRes = T();
        for(int i= 0; i < lht.pol.size();++i){
            // per ogni monomio appartenente a operando sx
            for(int j = 0; j < rht.pol.size();++j){
                // per ogni monomio appartenente a operando dx
                bd.mulConsistent(lht.pol[i].getCoefficiente(),rht.pol[j].getCoefficiente());
                // operazione di moltiplicazione tra coefficienti e' consistente
                bd.addConsistent(lht.pol[i].getGrado(),rht.pol[j].getGrado());
                // operazione di somma tra gradi e' consistente
                U coefficienteRisultante =
                        lht.pol[i].getCoefficiente() * rht.pol[j].getCoefficiente();
                if(coefficienteRisultante != 0){
                    bd.addConsistent(lht.pol[i].getGrado(),rht.pol[j].getGrado());
                    // operazione di somma tra gradi e' consistente
                    U gradoRisultante = lht.pol[i].getGrado() + rht.pol[j].getGrado();
                    bufferRes.pol.append(Monomio<U>(coefficienteRisultante,gradoRisultante));
                }
                // ogni elemento di operando sx e' stato moltiplicato per operando dx
                // e inserito in bufferRes
            }
        }
        // algoritmo di base ok
        std::sort(bufferRes.pol.begin(),bufferRes.pol.end());
        // bufferRes e' ordinato -> posso semplificare monomi con grado ==
        T res = T();
        int i = 0 ;
        while(i < bufferRes.pol.size()){
            U coeffGradiUguali = U();
            // coeffGradiUguali rappresenta coefficiente somma di tutti i
            // monomi di grado ==
            int j = i;

            // i, j  <  bufferRes.pol.size()
            while(j < bufferRes.pol.size() &&
                  bufferRes.pol[i].getGrado() == bufferRes.pol[j].getGrado()){
                bd.addConsistent(coeffGradiUguali,bufferRes.pol[j].getGrado());
                // somma consistente tra coefficiente parziale e coefficiente da
                // sommare
                coeffGradiUguali = coeffGradiUguali + bufferRes.pol[j].getCoefficiente();
                ++j;
            }
            // monomio puntato da j ha grado diverso rispetto a
            // monomio puntato da i or arrivato a fine di bufferRes
            // coeffGradiUguali contiene somma di tutti i coefficienti
            // di grado uguale a bufferRes.pol[i]
            res.pol.push_front(Monomio<U>(coeffGradiUguali,bufferRes.pol[i].getGrado()));
            i = j;
            // sposto indice in porzione di lista | grado predecessore < grado attuale
            // i eventualmente ==  bufferRes.pol.size()
        }
        return res;
    } catch(runtime_error& e){// raccoglie eccezioni overflow e underflow
        std::cout << e.what();
        throw e;
    }
    return T();
}


template<typename T,typename U>
T
PolynomialArithmeticExecutor<T,U>::reduxEqual(T& reduxPol){
    std::sort(reduxPol.pol.begin(),reduxPol.pol.end());
    // reduxPol e' ordinato -> posso semplificare monomi con grado ==
    T res = T();
    int i = 0 ;
    try{
        while(i < reduxPol.pol.size()){
            U coeffGradiUguali = U();
            // coeffGradiUguali rappresenta coefficiente somma di tutti i
            // monomi di grado ==
            int j = i;

            // i, j  <  reduxPol.pol.size()
            while(j < reduxPol.pol.size() &&
                  reduxPol.pol[i].getGrado() == reduxPol.pol[j].getGrado()){
                bd.addConsistent(coeffGradiUguali,reduxPol.pol[j].getGrado());
                // somma consistente tra coefficiente parziale e coefficiente da
                // sommare
                coeffGradiUguali = coeffGradiUguali + reduxPol.pol[j].getCoefficiente();
                ++j;
            }
            // monomio puntato da j ha grado diverso rispetto a
            // monomio puntato da i or arrivato a fine di reduxPol
            // coeffGradiUguali contiene somma di tutti i coefficienti
            // di grado uguale a reduxPol.pol[i]
            res.pol.push_front(Monomio<U>(coeffGradiUguali,reduxPol.pol[i].getGrado()));
            i = j;
            // sposto indice in porzione di lista | grado predecessore < grado attuale
            // i eventualmente ==  reduxPol.pol.size()
        }
        return res;
    }catch(runtime_error& e){// raccoglie eccezioni overflow e underflow
        std::cout << e.what();
        throw e;

    }
    return T();
}


#endif // POLYNOMIALARITHMETICEXECUTOR

