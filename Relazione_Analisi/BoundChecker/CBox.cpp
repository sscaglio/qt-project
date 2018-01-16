BoundChecker<T>

Membri interni

campi dati

const T upperBound
const T lowerBound

Interfaccia


metodi

BoundChecker(const T& uBound,const T& lBound)
  :upperBound(uBound),lowerBound(lBound)
{}

void
addConsistent(const T& lht,const T& rht)const
{
  if (((rht > 0) && (lht > (upperBound - rht)))) {
      throw Overflow;
    }
    else if  ((rht < 0) && (lht < (lowerBound - rht))){
      throw Underflow;
    } 
}
  
void
subConsistent(const T& lht,const T& rht) const{
    if (rht > 0 && lht < lowerBound + rht){
      throw Underflow;
    }
    else if((rht < 0 && lht > upperBound + rht)){
      throw Overflow;
    }
}

void
mulConsistent(const T& lht,const T& rht) const{
    if (lht > 0) {  /* lht is positive */
      if (rht > 0) {  /* lht and rht are positive */
	  if (lht > (upperBound / rht)) {
	    throw Overflow;
	  }
      } else { /* lht positive, rht nonpositive */
	if (rht < (lowerBound / lht)) {
	    throw Underflow;
	}
      } /* lht positive, rht nonpositive */
    } else { /* lht is nonpositive */
      if (rht > 0) { /* lht is nonpositive, rht is positive */
	  if (lht < (lowerBound / rht)) {
	    throw Underflow;
	  }
      } else { /* lht and rht are nonpositive */
	if ( (lht != 0) && (rht < (upperBound / lht))) {
	    throw Overflow;
	}
      } /* End if lht and rht are nonpositive */
    } /* End if lht is nonpositive */  
}


void
divConsistent(const T& lht,const T& rht) const{
  if (s_b == 0){
    throw DivisionByZero;
  }
  else((s_a == lowerBound) && (s_b == -1)) {
      throw OverFlow;
    }
}
