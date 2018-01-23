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

    Polinomio operator+(const Polinomio&)const;
    Polinomio operator-(const Polinomio&)const;
    Polinomio operator*(const Polinomio&)const;

    void testOperation()const;
    void printAll()const;
};


template<typename T>
const Boundchecker<T> Polinomio<T>::bd = Boundchecker<T>(numeric_limits<T>::max(),(-1) * numeric_limits<T>::max());

template<typename T>
Polinomio<T>::Polinomio(){}

template<typename T>
Polinomio<T>
Polinomio<T>::operator +(const Polinomio<T> & rht)const{

    int i = 0;
    int j = 0;
    Polinomio<T> res = Polinomio<T>();
    try{
        while(i < pol.size() && j < rht.pol.size()){
            if(pol[i].getGrado() == rht.pol[j].getGrado()){
                // gradi monomi uguali -> possibile somma
                bd.addConsistent(pol[i].getCoefficiente(),rht.pol[j].getCoefficiente());
                //somma consistente tra due monomi
                T coefficienteRisultante =
                        pol[i].getCoefficiente() + rht.pol[j].getCoefficiente();
                if(coefficienteRisultante != 0){
                    res.pol.append(Monomio<T>(coefficienteRisultante,pol[i].getGrado()));
                }
                ++i;
                ++j;
            }
            else{
                // gradi monomi distinti - > non possibile somma
                if(pol[i].getGrado() > rht.pol[j].getGrado()){
                    // grado primo monomio maggiore del secondo
                    res.pol.append(pol[i]);
                    ++i;
                }
                else{
                    // grado del secondo monomio maggiore del primo
                    res.pol.append(rht.pol[j]);
                    ++j;
                }
            }
        }
        Polinomio<T> rimanente = Polinomio<T>();
        if(i < pol.size()){
            // esistono elementi rimanenti nel polinomio sx
            rimanente.pol = pol.mid(i);
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
    return Polinomio<T>();
}

template<typename T>
Polinomio<T>
Polinomio<T>::operator -(const Polinomio<T> & rht)const{

    int i = 0;
    int j = 0;
    Polinomio<T> res = Polinomio<T>();
    try{
        while(i < pol.size() && j < rht.pol.size()){
            if(pol[i].getGrado() == rht.pol[j].getGrado()){
                // gradi monomi uguali -> possibile differenza
                bd.subConsistent(pol[i].getCoefficiente(),rht.pol[j].getCoefficiente());
                //sottrazione consistente tra due monomi
                T coefficienteRisultante =
                        pol[i].getCoefficiente() - rht.pol[j].getCoefficiente();
                if(coefficienteRisultante != 0){
                    res.pol.append(Monomio<T>(coefficienteRisultante,pol[i].getGrado()));
                }
                ++i;
                ++j;
            }
            else{
                // gradi monomi distinti - > non possibile differenza
                if(pol[i].getGrado() > rht.pol[j].getGrado()){
                    // grado primo monomio maggiore del secondo
                    res.pol.append(pol[i]);
                    ++i;
                }
                else{
                    // grado del secondo monomio maggiore del primo
                    // appendo negazione (poiche' operando destro di negazione)
                    // a risultato
                    res.pol.append(Monomio<T>((-1) * rht.pol[j].getCoefficiente(),rht.pol[j].getGrado()));
                    ++j;
                }
            }
        }
        Polinomio<T> rimanente = Polinomio<T>();
        if(i < pol.size()){
            // esistono elementi rimanenti nel polinomio sx
            rimanente.pol = pol.mid(i);
        }
        if(j < rht.pol.size()){
            // esistono elementi rimanenti nel polinomio dx
            rimanente.pol = rht.pol.mid(j);
            for(int i = 0 ; i < rimanente.pol.size();++i){
                rimanente.pol[i] =
                        Monomio<T>((-1) * rimanente.pol[i].getCoefficiente(),rimanente.pol[i].getGrado());
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
    return Polinomio<T>();
}

template<typename T>
Polinomio<T>
Polinomio<T>::operator *(const Polinomio<T>& rht)const{

    try{
        Polinomio<T> bufferRes = Polinomio<T>();
        for(int i= 0; i < pol.size();++i){
            // per ogni monomio appartenente a operando sx
            for(int j = 0; j < rht.pol.size();++j){
                // per ogni monomio appartenente a operando dx
                bd.mulConsistent(pol[i].getCoefficiente(),rht.pol[j].getCoefficiente());
                // operazione di moltiplicazione tra coefficienti e' consistente
                bd.addConsistent(pol[i].getGrado(),rht.pol[j].getGrado());
                // operazione di somma tra gradi e' consistente
                T coefficienteRisultante =
                        pol[i].getCoefficiente() * rht.pol[j].getCoefficiente();
                if(coefficienteRisultante != 0){
                    bd.addConsistent(pol[i].getGrado(),rht.pol[j].getGrado());
                    // operazione di somma tra gradi e' consistente
                    T gradoRisultante = pol[i].getGrado() + rht.pol[j].getGrado();
                    bufferRes.pol.append(Monomio<T>(coefficienteRisultante,gradoRisultante));
                }
                // ogni elemento di operando sx e' stato moltiplicato per operando dx
                // e inserito in bufferRes
            }
        }
        // algoritmo di base ok
        std::sort(bufferRes.pol.begin(),bufferRes.pol.end());
          // bufferRes e' ordinato -> posso semplificare monomi con grado ==
          Polinomio<T> res = Polinomio<T>();
          int i = 0 ;
          while(i < bufferRes.pol.size()){
            T coeffGradiUguali = T();
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
            res.pol.push_front(Monomio<T>(coeffGradiUguali,bufferRes.pol[i].getGrado()));
            i = j;
            // sposto indice in porzione di lista | grado predecessore < grado attuale
            // i eventualmente ==  bufferRes.pol.size()
          }
          return res;
    } catch(runtime_error& e){// raccoglie eccezioni overflow e underflow
        std::cout << e.what();
    }
    return Polinomio<T>();
}

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

