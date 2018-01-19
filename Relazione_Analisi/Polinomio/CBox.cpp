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
	  // se coefficiente risultante e' 0 -> monomio e' nullo -> non devo appenderlo a
	  // res risultato
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
Polinomio<T>::operator-()const{
  int i = 0;
  int j = 0;
  Polinomio<T> res = Polinomio<T>();
  try{
    while(i < pol.size() && j < rht.pol.size()){
      if(pol[i].getGrado() == rht.pol[j].getGrado()){
	// gradi monomi uguali -> possibile differenza
	bd.subConsistent(pol[i].getCoefficiente(),rht.pol[j].getCoefficiente());
	//differenza consistente tra due monomi
	T coefficienteRisultante =
	  pol[i].getCoefficiente() - rht.pol[j].getCoefficiente();
	if(coefficienteRisultante != 0){
	  // sse coefficiente ==  0 -> monomio nullo -> non posso appendere
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
	  // devo negare coefficiente essendo operando destro di operazione
	  res.pol.append(Monomio<T>((-1) * rht.pol[j].getCoefficiente()),rht.pol[j].getGrado());
	  ++j;
	}
      }
    }
    Polinomio<T> rimanente = Polinomio<T>();
    if(i < pol.size()){
      // esistono elementi rimanenti nel polinomio sx
      // operando destro non deve avere elementi negati nel coefficiente
      rimanente.pol = pol.mid(i);
    }
    if(j < rht.pol.size()){
      // esistono elementi rimanenti nel polinomio dx
      // poiche elemento e' operando destro -> devo negare segno
      // di ogni Monomio di rimanente
      rimanente.pol = rht.pol.mid(j);
      for(int i = 0 ; i < rimanente.size() ; ++i){
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
Polinomio<T>::operator*()const{}
