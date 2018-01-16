//MatriceConcreta<T>


mambri interni

campi dati

QVector<T> matrice
const unsigned int righe
const unsigned int colonne
static const Boundchecker<T> bd


Interfaccia

metodi

Matrice(unsigned int r,unsigned int c):
       matrice(QVector()),righe(r),colonne(c){
}

Matrice*
operator+(const Matrice& rht)const{
  try{
    if(((righe != rht.righe) ||
	 (colonne != rht.colonne))){// dimensioni non consistenti
      throw domain_error("dimensioni matrice non consistenti");
    }
    Matrice<T> *res = new Matrice<T>(righe * colonne);
    for(int indiceElt = 0;
	indiceElt < matrice.size();
	++indiceElt){
      int sommaElemento = 0;
      if(bd.addConsistent(matrice[i],rht.matrice[i])){
	sommaElemento = matrice[i] + rht.matrice[i];
      }
      res[i] = sommaElemento;
    }
    return res;
  }catch(exception & e){
    res.clear();// elimina ogni elemento appartente a res
    e.what();// stampa messaggio errore
  }
}


Matrice*
operator-(const Matrice& rht)const{
  try{
    if(!((righe == rht.righe) ||
	 (colonne != rht.colonne))){// dimensioni non consistenti
      throw domain_error("dimensioni matrice non consistenti");
    }
    Matrice<T> *res = new Matrice<T>(righe * colonne);
    for(int indiceElt = 0;
	indiceElt < matrice.size();
	++indiceElt){
      int differenzaElemento = 0;
      if(bd.subConsistent(matrice[i],rht.matrice[i])){
	differenzaElemento = matrice[i] - rht.matrice[i];
      }
      res[i] = differenzaElemento;
    }
    return res;
  }catch(exception & e){
    res.clear();// elimina ogni elemento appartente a res
    e.what();// stampa messaggio errore
  }
}



Matrice*
operator*(const Matrice& rht)const{
  try{
    if(colonne != rht.righe)
      throw domain_error("dimensioni matrice non consistenti");
    }
    Matrice<T> *res = new Matrice<T>(righe * rht.colonne);
    for(int i = 0 ; i < righe;++i){
      for(int j = 0; j < rht.colonne;++j){
	T sommaParziale = T();
	for(int k = 0; k < colonne;++i){
	  if(bd.addConsistent
	     (matrice[righe * i + k],rht.matrice[rht.colonne * k + j])){
	    sommaParziale =
	      matrice[righe * i + k] + rht.matrice[rht.colonne * k + j];
	  }
	}
	res.push_back(sommaParziale);
      }
    }
    
    return res;
  }catch(exception & e){
    res.clear();// elimina ogni elemento appartente a res
    e.what();// stampa messaggio errore
  }
}

