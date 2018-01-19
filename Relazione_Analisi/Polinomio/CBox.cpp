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

  void testSum(){
    Polinomio<Monomio<T>> p1;
    Polinomio<Monomio<T>> p2;

    for(int i = 0 ; i < 4;++i){
      p1.append(Monomio<T>(i,i));
      p2.append(Monomio<T>(i,i));
    }
    Polinomio<Monomio<T>> res = p1 + p2;
    res.printAll();

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
    while(i < pol.size() && j < rht.pol.size()){
      // se monomi attuali di lht == rht
      // -> possibile definire somma tra monomi
      if(pol[i] == pol[j]){
	bd.addConsistent
	  (pol[i].getCoefficiente(),
	   pol[j].getCoefficiente()); 
	T coefficienteRisultante =
	  pol[i].getCoefficiente() + pol[j].getCoefficiente());
      Monomio<T> risultante =
	Monomio<T>(coefficienteRisultante,pol[i].getGrado());
      res.append(risultante);
      ++i;
      ++j;
    }
    else{
      // monomi distinti

      // se monomio di lht > monomio rht
      // -> appendi monomio sx a res , incrementa
      // contatore di sx (<->i)
      if(pol[i] > pol[j]){
	res.append(pol[i]);
	++i;
      }
      // se monomio di lht < monomio rht
      // -> appendi monomio dx a res , incrementa
      // contatore di dx (<->j)
      else{
	res.append(pol[j]);
	++j;
      }
    }
  }
  QList<Monomio> rimanente = QList<Monomio>();
  if(j < rht.pol.size()){
    // esistono elementi in polinomio rht
    rimanente = rht.pol.mid(j);
  }
  if(i < pol.size() ){
    // esistono elementi in polinomio lht
    rimanente = rht.pol.mid(i);
  }
  if(!(rimanente.empty())){
    res.append(rimanente);
  }
  return res;
}catch(runtime_error &e){
  std::cout << e.what() << std::endl;
 }
return Polinomio<T>();
}

template<typename T>
Polinomio<T>
Polinomio<T>::operator-()const{}

template<typename T>
Polinomio<T>
Polinomio<T>::operator*()const{}
