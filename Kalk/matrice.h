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

using std::cout;
using std::endl;

template<typename T>
class Matrice{// eredita da classe astratta MatriceAstratta

    QVector<T> matrice;
    unsigned int righe;
    unsigned int colonne;

    static Boundchecker<T> bd;

public:
    Matrice(const unsigned int = 0,const unsigned int = 0);

    Matrice* operator+(const Matrice&)const ;
    Matrice* operator-(const Matrice&)const ;
    Matrice* operator*(const Matrice&)const ;

    //test fn
    void insertValue(const T& val){
        matrice.push_back(val);
    }

    void printAll(){
        for(unsigned int i = 0 ; i < righe * colonne;++i){
            std::cout << matrice[i] << " ";
        }
        std::cout << std::endl;
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
// sistemato problema memory leak in caso di condizioni eccezionali
// sollevate all'interno del ciclo
template<typename T>
Matrice<T>*
Matrice<T>::operator +(const Matrice<T>& rht) const{

    Matrice<T> *res = 0;// puntatore a matrice risultato
    try{
        if(!(righe == rht.righe && colonne == rht.colonne)){
            throw domain_error("dimensione matrici non compatibili");
        }
        res = new Matrice<T>(righe,colonne);// puo' causare errori di allocazione
        for(unsigned int i = 0 ;i < (righe * colonne);++i){
            T sommaElemento = T();
            bd.addConsistent(matrice[i],rht.matrice[i]);
            sommaElemento = matrice[i] + rht.matrice[i];
            res->matrice.push_back(sommaElemento);
        }// ogni elemento di res e' definito
        // non sollevati errori di allocazione e dimensione matrici consistenti
        return res;
    }
    catch(bad_alloc & e){// necessario gestire situazione memoria indisponibile??
        std::cout << "allocation failed " << e.what() << std::endl;
    }
    catch(runtime_error & e){// errori overflow, underflow etc
        std::cout << e.what() << std::endl;
        delete res;
    }
    catch(logic_error & e){// errore dimensioni non compatibili(da rimuovere in futuro)
        std::cout << e.what() << std::endl;
    }
    return 0;// ritorna puntatore nullo in caso sia stata sollevata almeno 1 delle precedenti eccezioni
}

// operatore differenza tra tipi matrice
// testato errore dimensioni non compatibili
// sistemato problema memory leak in caso di condizioni eccezionali
// sollevate all'interno del ciclo
template<typename T>
Matrice<T>*
Matrice<T>::operator -(const Matrice<T>& rht) const{

    Matrice<T> *res = 0;// puntatore a matrice risultato
    try{
        if(!(righe == rht.righe && colonne == rht.colonne)){
            throw domain_error("dimensione matrici non compatibili");
        }
        res = new Matrice<T>(righe,colonne);// puo' causare errori di allocazione
        for(unsigned int i = 0 ;i < (righe * colonne);++i){
            T differenzaElemento = T();
            bd.subConsistent(matrice[i],rht.matrice[i]);
            differenzaElemento = matrice[i] - rht.matrice[i];
            res->matrice.push_back(differenzaElemento);
        }// ogni elemento di res e' definito
        // non sollevati errori di allocazione e dimensione matrici consistenti
        return res;
    }
    // necessario gestire situazione memoria indisponibile??
    catch(bad_alloc & e){
        std::cout << "allocation failed " << e.what() << std::endl;
    }
    catch(runtime_error & e){// errori overflow, underflow etc
        std::cout << e.what() << std::endl;
        delete res;
    }
    catch(logic_error & e){// errore dimensioni non compatibili(da rimuovere in futuro)
        std::cout << e.what() << std::endl;
    }
    return 0;// ritorna puntatore nullo in caso sia stata sollevata almeno 1 delle precedenti eccezioni
}


// operatore differenza tra tipi matrice
// testato errore dimensioni non compatibili
// sistemato problema memory leak in caso di condizioni eccezionali
// sollevate all'interno del ciclo
// testa effettiva correttezza operatore di moltiplicazione
template<typename T>
Matrice<T>*
Matrice<T>::operator *(const Matrice<T>& rht) const{

    Matrice<T> *res = 0;// puntatore a matrice risultato
    try{
        if(!(colonne != rht.righe)){
            throw domain_error("dimensione matrici non compatibili");
        }
        res = new Matrice<T>(righe,rht.colonne);
        for(int i = 0 ;i < righe;++i){
            for(int j = 0; j < rht.colonne;++j){
                T prodottoParziale = T();
                for(int k = 0; k < colonne;++k){
                    T sommaParziale = T();
                    bd.mulConsistent(matrice[righe * i + k],rht.matrice[rht.colonne * k + j]);
                    sommaParziale = matrice[righe * i + k] + rht.matrice[rht.colonne * k + j];
                    bd.addConsistent(sommaParziale,prodottoParziale);
                    prodottoParziale = prodottoParziale + sommaParziale;
                }
                res->matrice.push_back(prodottoParziale);
            }
        }
        // ogni elemento di matrice risultante e' definito, nessuna eccezione sollevata
        return res;
    }
    // necessario gestire situazione memoria indisponibile??
    catch(bad_alloc & e){
        std::cout << "allocation failed " << e.what() << std::endl;
    }
    catch(runtime_error & e){// errori overflow, underflow etc
        std::cout << e.what() << std::endl;
        delete res;
    }
    catch(logic_error & e){// errore dimensioni non compatibili(da rimuovere in futuro)
        std::cout << e.what() << std::endl;
    }
    return 0;// ritorna puntatore nullo in caso sia stata sollevata almeno 1 delle precedenti eccezioni
}
#endif // MATRICE

