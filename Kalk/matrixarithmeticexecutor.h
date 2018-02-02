#ifndef MATRIXARITHMETICEXECUTOR
#define MATRIXARITHMETICEXECUTOR

#include "boundchecker.h"

template<typename T,typename U>
class MatrixArithmeticExecutor{

    static const Boundchecker<U> bd;
public :
    static T add(const T&,const T&);
    static T sub(const T&,const T&);
    static T mul(const T&,const T&);
};

template<typename T,typename U>
const Boundchecker<U>
MatrixArithmeticExecutor<T,U>::bd =
           Boundchecker<U>(std::numeric_limits<U>::max(),(-1) * std::numeric_limits<U>::max());


template<typename T,typename U>
T
MatrixArithmeticExecutor<T,U>::add(const T& lht,const T& rht){
    try{
        if(!(lht.righe == rht.righe && lht.colonne == rht.colonne)){
            throw domain_error("dimensione matrici non compatibili");
        }
       T res = T(lht.righe,lht.colonne);
        for(unsigned int i = 0 ;i < (lht.righe * lht.colonne);++i){
            U sommaElemento = U();
            bd.addConsistent(lht.matrice[i],rht.matrice[i]);
            sommaElemento = lht.matrice[i] + rht.matrice[i];
            res.matrice.push_back(sommaElemento);
        }// ogni elemento di res e' definito
        // non sollevati errori di allocazione e dimensione matrici consistenti
        return res;
    }
    catch(runtime_error & e){// errori overflow, underflow etc
        std::cout << e.what() << std::endl;
        throw e;
    }
    catch(logic_error & e){// errore dimensioni non compatibili(da rimuovere in futuro)
        std::cout << e.what() << std::endl;
        throw e;
    }
    return T(0,0);// ritorna puntatore nullo in caso sia stata sollevata almeno 1 delle precedenti eccezioni
}

template<typename T,typename U>
T
MatrixArithmeticExecutor<T,U>::sub(const T& lht,const T&rht){
    try{
        if(!(lht.righe == rht.righe && lht.colonne == rht.colonne)){
            throw domain_error("dimensione matrici non compatibili");
        }
        T res = T(lht.righe,lht.colonne);// puo' causare errori di allocazione
        for(unsigned int i = 0 ;i < (lht.righe * lht.colonne);++i){
            U differenzaElemento = U();
            bd.subConsistent(lht.matrice[i],rht.matrice[i]);
            differenzaElemento = lht.matrice[i] - rht.matrice[i];
            res.matrice.push_back(differenzaElemento);
        }// ogni elemento di res e' definito
        // non sollevati errori di allocazione e dimensione matrici consistenti
        return res;
    }
    catch(runtime_error & e){// errori overflow, underflow etc
        std::cout << e.what() << std::endl;
        throw e;
    }
    catch(logic_error & e){// errore dimensioni non compatibili(da rimuovere in futuro)
        std::cout << e.what() << std::endl;
        throw e;
    }
    return T(0,0);// ritorna puntatore nullo in caso sia stata sollevata almeno 1 delle precedenti eccezioni
}

template<typename T,typename U>
T
MatrixArithmeticExecutor<T,U>::mul(const T& lht,const T&rht){
    try{
        if(lht.colonne != rht.righe){
            throw domain_error("dimensione matrici non compatibili");
        }
        T res = T(lht.righe,rht.colonne);
        for(unsigned int i = 0 ;i < lht.righe;++i){
            for(unsigned int j = 0; j < rht.colonne;++j){
                U risultatoParziale = U();
                for(unsigned int k = 0; k < lht.colonne;++k){
                    U prodottoParziale = U();
                    bd.mulConsistent(lht.matrice[lht.colonne * i + k],rht.matrice[rht.colonne * k + j]);
                    prodottoParziale = lht.matrice[lht.colonne * i + k] * rht.matrice[rht.colonne * k + j];
                    bd.addConsistent(risultatoParziale,prodottoParziale);
                    risultatoParziale = risultatoParziale + prodottoParziale;
                }
                res.matrice.push_back(risultatoParziale);
            }
        }
        // ogni elemento di matrice risultante e' definito, nessuna eccezione sollevata
        return res;
    }
    catch(runtime_error & e){// errori overflow, underflow etc
        std::cout << e.what() << std::endl;
        throw e;
    }
    catch(logic_error & e){// errore dimensioni non compatibili(da rimuovere in futuro)
        std::cout << e.what() << std::endl;
        throw e;
    }
    return T(0,0);
}
#endif // MATRIXARITHMETICEXECUTOR

