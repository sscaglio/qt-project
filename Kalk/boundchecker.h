#ifndef BOUNDCHECKER
#define BOUNDCHECKER

#include<iostream>
#include<limits>
#include<stdexcept>

#include "dividebyzero_error.h"

using std::cout;
using std::endl;
using std::numeric_limits;
using std::overflow_error;
using std::underflow_error;

template<typename T>
class Boundchecker{

    const T upperBound;
    const T lowerBound;

public:

    Boundchecker(const T&,const T&);
    void addConsistent(const T&,const T&)const;
    void subConsistent(const T&,const T&)const;
    void mulConsistent(const T&,const T&)const;
    void divConsistent(const T&,const T&)const;
};


template<typename T>
Boundchecker<T>::Boundchecker(const T& uBound,const T&lBound)
    : upperBound(uBound),lowerBound(lBound)
{}

// branch coverage 100%
// per tipi double e int
template<typename T>
void
Boundchecker<T>::addConsistent(const T & lht, const T & rht ) const{
    if ((rht > 0) && (lht > (upperBound - rht))) {
        throw overflow_error("overflow error in operazione di addizione");
    }
    else if  ((rht < 0) && (lht < (lowerBound - rht))){
        throw underflow_error("underflow error in operazione di addizione");
    }
}


// branch coverage 100 %
// per tipi int e double

template<typename T>
void
Boundchecker<T>::subConsistent(const T & lht, const T & rht) const{

    if (rht > 0 && lht < lowerBound + rht){
        throw underflow_error("underflow error in operazione di sottrazione");
    }
    else if((rht < 0 && lht > upperBound + rht)){
        throw overflow_error("overflow error in operazione di sottrazione");
    }
}

// test non completo
// branch coverage < 100
template<typename T>
void
Boundchecker<T>::mulConsistent(const T & lht, const T & rht) const{
    if (lht > 0) {  /* lht is positive */
        if (rht > 0) {  /* lht and rht are positive */
            if (lht > (upperBound / rht)) {
                throw overflow_error("overflow error in operazione di moltiplicazione, termine sinistro e destro positivi");
            }
        } else { /* lht positive, rht nonpositive */
            if (rht < (lowerBound / lht)) {
                throw underflow_error("underflow error in operazione di moltiplicazione, termine sinistro positivo, destro negativo");
            }
        } /* lht positive, rht nonpositive */
    } else { /* lht is nonpositive */
        if (rht > 0) { /* lht is nonpositive, rht is positive */
            if (lht < (lowerBound / rht)) {
                throw underflow_error("underflow error in operazione di moltiplcazione, termine sinistro negativo, destro positivo");
            }
        } else { /* lht and rht are nonpositive */
            if ( (lht != 0) && (rht < (upperBound / lht))) {
                throw overflow_error("overflow error in operazione di moltiplicazione, termine sinistro e destro negativi");
            }
        } /* End if lht and rht are nonpositive */
    } /* End if lht is nonpositive */
}

// branch coverage 100 %
// per tipi int e double

template<typename T>
void
Boundchecker<T>::divConsistent(const T & lht, const T & rht) const{
    if (rht == 0){
        throw dividebyzero_error("divide by zero error in operazione di divisione");
    }
    else if((lht == lowerBound) && (rht == -1)) {
        throw overflow_error("overflow error in operazione di divisione");
    }
}


#endif // BOUNDCHECKER

