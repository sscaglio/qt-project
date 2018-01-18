// CLEAR BOX
template<typename T>

class Polinomio{

  QList<Monomio<T>> pol;

  static const BoundChecker<T> bd;
  
public:

  Polinomio();// costruttore di default
  // nessun argomento , inserimento successivo

  operator+(const Polinomio<T>& rht)const;
  operator-(const Polinomio<T>& rht)const;
  operator*(const Polinomio<T>& rht)const;

  void printAll(){
    for(int i = 0 ; i < pol.size();i++){
      std::cout << pol." "
	}
  }
};


template<typename T>
Polinomio<T>
Polinomio<T>::operator+(const Polinomio<T>& rht)const{
  // precondizione:Polinomi sono ordinati per
  // ordine di grado discendente
  try{
    Polinomio<T> res = Polinomio<T>();

    int i = 0;
    int j = 0;
    for(;++i,++j){}
    // solo Polinomio lht e' vuoto -> appendi rht a res
    return res.append(rht);
    // solo Polinomio rht e' vuoto -> appendi lht a res
    return res;
  }catch(runtime_error &e){
    std::cout << e.what() << std::endl;
  }
  return Polinlomio();
}

template<typename T>
Polinomio<T>
Polinomio<T>::operator-()const{}

template<typename T>
Polinomio<T>
Polinomio<T>::operator*()const{}
