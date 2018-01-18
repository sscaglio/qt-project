//CBOX

template<typename T>
class Monomio{

  const T coefficiente;
  const unsigned int grado;

  BoundChecker<T> bd;

public:

  friend ostream& operator<< <T>(ostream &,const Monomio<T>&);
  Monomio(const T = T(),const unsigned int g = unsigned int(1))
  
  Monomio operator+(const Monomio&)const;
  Monomio operator-(const Monomio&)const;
  Monomio operator*(const Monomio&)const;
  Monomio operator/(const Monomio&)const;

  bool operator>(const Monomio&)const;
};

<typename T>
Monomio<T>
Monomio<T>::operator+(const Monomio<T>& rht)const{
  try{
    bd.addConsistent(coefficiente,rht.coefficiente);
    // somma consistente tra coefficienti sx e dx
    T coefficienteRisultante = coefficiente + rht.coefficiente;
    return Monomio(coefficienteRisultante,grado);
  }catch(runtime_error & e){
    std::cout << e.what() << std::endl;
  }
  return Monomio();
}

<typename T>
Monomio<T>
Monomio<T>::operator-(const Monomio<T>& rht)const{
  try{
    bd.subConsistent(coefficiente,rht.coefficiente);
    // differenza consistente tra coefficienti sx e dx
    T coefficienteRisultante = coefficiente - rht.coefficiente;
    return Monomio(coefficienteRisultante,grado);
  }catch(runtime_error & e){
    std::cout << e.what() << std::endl;
  }
  return Monomio();
}

<typename T>
Monomio<T>
Monomio<T>::operator*(const Monomio<T>& rht)const{
  try{
    bd.mulConsistent(coefficiente,rht.coefficiente);
    // prodotto consistente tra coefficienti sx e dx
    T coefficienteRisultante = coefficiente * rht.coefficiente;

    bd.addConsistent(grado,rht.grado);
    // somma gradi consistente tra monomio sx e dx
    unsigned int gradoRisultante = grado + rht.grado;
    return Monomio(coefficienteRisultante,gradoRisultante);
  }catch(runtime_error & e){
    std::cout << e.what() << std::endl;
  }
  return Monomio();
}



<typename T>
Monomio<T>
Monomio<T>::operator/(const Monomio<T>& rht)const{
  // coefficiente sx e dx qualsiasi
  try{
    bd.divConsistent(coefficiente,rht.coefficiente);
    // divisione consistente tra coefficienti sx e dx
    T coefficienteRisultante = coefficiente / rht.coefficiente;
    bd.subConsistent(grado,rht.grado);
    // differenza consistente tra grado monomio sx e dx
    unsigned int gradoRisultante = grado - rht.grado;
    return Monomio(coefficienteRisultante,gradoRisultante);
  }catch(runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

template<typename T>
bool
Monomio<T>::operator>(const Monomio<T>& rht)const {
  return grado > rht.grado ||
    (grado == rht.grado && coefficiente > rht.coefficiente);
}

template<typename T>
ostream&
Monomio<T>::operator<<(ostream & lht,const Monomio<T>& rht){
  return lht << rht.coefficiente << "x" << "^" << rht.grado;
}
