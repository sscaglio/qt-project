#ifndef BOUNDCHECKER
#define BOUNDCHECKER

#include<iostream>
#include<limits>

using std::cout;
using std::endl;
using std::numeric_limits;

template<typename T>
class Boundchecker{

    const T upperBound;
    const T lowerBound;

public:

    Boundchecker(const T&,const T&);
    bool addConsistent(const T&,const T&)const;
    bool subConsistent(const T&,const T&)const ;
    bool mulConsistent(const T&,const T&)const;
    bool divConsistent(const T&,const T&)const;


    void testChecker();
    bool testAdd();
    bool testSub();
    bool testMul();
    bool testDiv();
};


template<typename T>
Boundchecker<T>::Boundchecker(const T& uBound,const T&lBound)
    : upperBound(uBound),lowerBound(lBound)
{}

// branch coverage 100%
// per tipi double e int
template<typename T>
bool
Boundchecker<T>::addConsistent(const T & lht, const T & rht ) const{

    if ((rht > 0) && (lht > (upperBound - rht))) {
        //throw Overflow();
        return false;
    }
    else if  ((rht < 0) && (lht < (lowerBound - rht))){
        return false;
        //throw Underflow();
    } else {
        return true;
    }
}


// branch coverage 100 %
// per tipi int e double

template<typename T>
bool
Boundchecker<T>::subConsistent(const T & lht, const T & rht) const{

    if (rht > 0 && lht < lowerBound + rht){
        return false;
        //throw Underflow;
    }
    else if((rht < 0 && lht > upperBound + rht)){
        return false;
        //throw Overflow;
    } else {
        return true;
    }
}

// test non completo
// branch coverage < 100
template<typename T>
bool
Boundchecker<T>::mulConsistent(const T & lht, const T & rht) const{
    if (lht > 0) {  /* lht is positive */
        if (rht > 0) {  /* lht and rht are positive */
            if (lht > (upperBound / rht)) {
                //throw Overflow;
                return false;
            }
        } else { /* lht positive, rht nonpositive */
            if (rht < (lowerBound / lht)) {
               // throw Underflow;
                return false;
            }
        } /* lht positive, rht nonpositive */
    } else { /* lht is nonpositive */
        if (rht > 0) { /* lht is nonpositive, rht is positive */
            if (lht < (lowerBound / rht)) {
                //throw Underflow;
                return false;
            }
        } else { /* lht and rht are nonpositive */
            if ( (lht != 0) && (rht < (upperBound / lht))) {
                //throw Overflow;
                return false;
            }
        } /* End if lht and rht are nonpositive */
    } /* End if lht is nonpositive */
    return true;

}


// branch coverage 100 %
// per tipi int e double

template<typename T>
bool
Boundchecker<T>::divConsistent(const T & lht, const T & rht) const{
    if ((rht == 0)){
        //throw DivisionByZero;
        return false;
    }
    else if((lht == lowerBound) && (rht == -1)) {
        //throw OverFlow;
        return false;
    }
    else {
        return true;
    }

}

template<typename T>
bool
Boundchecker<T>::testAdd(){
    std::cout << "add tst" << std::endl;

    bool tst1 = false;
    bool tst2 = false;
    bool tst3 = false;
    if(!addConsistent(numeric_limits<T>::max(),(numeric_limits<T>::max()))){
        std::cout << "test1 ok" << std::endl;
        tst1 = true;
    }
    if(!addConsistent((-1)*(numeric_limits<T>::max()),(-1)*(numeric_limits<T>::max()))){
        std::cout << "test2 ok" << std::endl;
        tst2 = true;
    }
    if(addConsistent(1.1,2.2)){
        std::cout << "test3 ok" << std::endl;
        tst3 = true;
    }
    return tst1 && tst2 && tst3;
}


template<typename T>
bool
Boundchecker<T>::testSub(){
    std::cout << "sub tst" << std::endl;

    bool tst1 = false;
    bool tst2 = false;
    bool tst3 = false;

    if(!subConsistent((-1)*numeric_limits<T>::max(),(numeric_limits<T>::max()))){
        std::cout << "test1 ok" << std::endl;
        tst1 = true;
    }
    if(!subConsistent((-1)*(numeric_limits<T>::max()),(numeric_limits<T>::max()))){
        std::cout << "test2 ok" << std::endl;;
        tst2 = true;
    }
    if(subConsistent(1.1,2.2)){
        std::cout << "test3 ok" << std::endl;
        tst3 = true;
    }
    return tst1 && tst2 && tst3;
}

template<typename T>
bool
Boundchecker<T>::testMul(){

    std::cout << "mul tst" << std::endl;

    bool tst1 = false;
    bool tst2 = false;
    bool tst3 = false;

    if(!mulConsistent(numeric_limits<T>::max(),(numeric_limits<T>::max()))){
        std::cout << "test1 ok" << std::endl;
        tst1 = true;
    }
    if(!mulConsistent((-1)*(numeric_limits<T>::max()),(-1)*(numeric_limits<T>::max()))){
        std::cout << "test2 ok" << std::endl;
        tst2 = true;
    }
    if(mulConsistent(1.1,2.2)){
        std::cout << "test3 ok" << std::endl;
        tst3 = true;
    }
    return tst1 && tst2 && tst3;
}

template<typename T>
bool
Boundchecker<T>::testDiv(){
    std::cout << "div tst" << std::endl;

    bool tst1 = false;
    bool tst2 = false;
    bool tst3 = false;

    if(!divConsistent(100,0)){
        std::cout << "test1 ok" << std::endl;
        tst1 = true;
    }
    if(!divConsistent((numeric_limits<int>::min()),-1)){
        // attenzione:se numeric_limits<T> ha T = int e valore passato per il controllo e' -1 * MIN_INT -> comportamento scorretto
        // ai fini dell'esecuzione tutto ok
        std::cout << "test2 ok" << std::endl;
        tst2 = true;
    }
    if(divConsistent(4,2)){
        std::cout << "test3 ok" << std::endl;
        tst3 = true;
    }
    return tst1 && tst2 && tst3;
}

template<typename T>
void
Boundchecker<T>::testChecker(){

    if(testAdd()){
        std::cout << "test add ok" << std::endl;
    }
    if(testSub()){
        std::cout << "test sub ok" << std::endl;
    }
    if(testMul()){
        std::cout << "test mul ok" << std::endl;
    }
    if(testDiv()){
        std::cout << "test div ok" << std::endl;
    }

}

#endif // BOUNDCHECKER

