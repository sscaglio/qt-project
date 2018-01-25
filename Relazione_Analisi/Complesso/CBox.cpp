// complesso concreto

membri interni

const T reale
const T immaginaria
static const Boundchecker<T> bd


interfaccia

metodi

complesso(const T& r,const T& i)
  :reale(r),immaginaria(i){}

Complesso
operator+(const Complesso& rht){
  ;
  try{
    addConsistent(reale,rht.reale);
    addConsistent(immaginaria,rht.immaginaria);
    // consistenza parte immaginaria e reale
    res = new Complesso(reale + rht.reale,immaginaria + rht.immaginaria);
    // effettiva allocazione complesso
    return res;
    // complesso e' effetivamente ritornato
  }
  catch(runtime_error& e){//cattura errori di overflow e underflow
    std::cout << e.what() << std::endl;
    ;
  }
  catch(bad_allocation& e){// cattura errori di allocazione non riuscita
    std::cout << e.what() << std::endl;
    ;// ?
  }
  return 0;
}


Complesso
operator-(const Complesso& rht){
  ;
  try{
    subConsistent(reale,rht.reale);
    subConsistent(immaginaria,rht.immaginaria);
    // consistenza parte immaginaria e reale
    res = new Complesso(reale - rht.reale,immaginaria - rht.immaginaria);
    // effettiva allocazione complesso
    return res;
    // complesso e' effetivamente ritornato
  }
  catch(runtime_error& e){//cattura errori di overflow e underflow
    std::cout << e.what() << std::endl;
    ;
  }
  catch(bad_allocation& e){// cattura errori di allocazione non riuscita
    std::cout << e.what() << std::endl;
    ;// ?
  }
  return 0;
}



Complesso
operator*(const Complesso& rht){
  ;
  try{
    mulConsistent(reale,rht.reale);
    T primoTermine = reale * rht.reale;
    mulConsistent(immaginaria,rht.immaginaria);
    T secondoTermine = immaginaria * rht.immaginaria;
    // ac e bd consistenti
    mulConsistent(immaginaria,rht.reale);
    T terzoTermine = immaginaria * rht.reale;
    mulConsistent(reale,rht.immaginaria);
    T quartoTermine = reale * rht.immaginaria;
    // bc e ad consistenti 
    subConsistent(primoTermine,secondoTermine);
    // ac - bd consistente;
    addConsistent(terzoTermine,quartoTermine);
    // bc + ad consistente

    // -> (ac - bd) - (bc + ad) consistente
    return Complesso(primoTermine - secondoTermine,terzoTermine + quartoTermine);
  }
  catch(runtime_error& e){//cattura errori di overflow e underflow
    std::cout << e.what() << std::endl;
    ;
  }
  return 0;
}



Complesso
operator/(const Complesso& rht){
  ;
  try{
    divConsistent(reale,rht.reale);
    divConsistent(immaginaria,rht.immaginaria);
    // consistenza parte immaginaria e reale
    res = new Complesso(reale / rht.reale,immaginaria / rht.immaginaria);
    // effettiva allocazione complesso
    return res;
    // complesso e' effetivamente ritornato
  }
  catch(runtime_error& e){//cattura errori di overflow e underflow
    std::cout << e.what() << std::endl;
    ;
  }
  catch(bad_allocation& e){// cattura errori di allocazione non riuscita
    std::cout << e.what() << std::endl;
    ;// ?
  }
  return 0;
}



ComplessoInt
ComplessoInt::factorial()const{
  int factorialReale = this->getReale();
  int factorialImmaginaria = this->getImmaginaria();
  int daMoltReale = factorialReale - 1;
  int daMoltImmaginaria = factorialImmaginaria - 1;
  while(daMoltReale > 1){
    bd.mulConsistent(factorialReale,daMoltReale);
    factorialReale*=daMoltReale;
    --daMoltReale;
  }
  // nessun overflow underflow in operazione di fattoriale per parte reale
  while(daMoltImmaginaria > 1){
    bd.mulConsistent(factorialImmaginaria,daMoltImmaginaria);
    factorialImmaginaria*=daMoltImmaginaria;
    --daMoltImmaginaria;
  }
  // nessun overflow underflow in operazione di fattoriale per parte immaginaria
  return ComplessoInt(factorialReale,factorialImmaginaria);
  
}
