#ifndef POLINOMIO
#define POLINOMIO

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
    for(int i = 3; i > 0;--i){
        p1.pol.append(Monomio<T>(i,i));
        p2.pol.append(Monomio<T>(i,1 + i));
    }


    std::cout << "PRIMO POLINOMIO " << std::endl;
    p1.printAll();

    std::cout<< "SECONDO POLINOMIO" << std::endl;
    p2.printAll();


    res = p1 - p2;
    std::cout << "RISULTATO SOMMA" << std::endl;
    res.printAll();
    cout << std::endl;
}

#endif // POLINOMIO

