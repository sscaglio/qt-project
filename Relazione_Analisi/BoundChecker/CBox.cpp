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

bool
addConsistent(const T& lht,const T& rht)
{
  if (((rht > 0) && (lht > (upperBound - rht))) {
      throw IntegerOverflow;
    }
    else if  ((rht < 0) && (lht < (lowerBound - rht))){
      throw IntegerUnderflow;
    } else {	
      sum = lht + rht;
    }
    return sum;
    }
}
catch(const Overflow& e){
  print "overflow";
 }
 catch(const UnderFlow& e){
   print "underflow";
 }

subConsistent(const T& lht,const T& {
    T diff;
    if ((rht > 0 && lht < INT_MIN + rht) ||
	(rht < 0 && lht > INT_MAX + rht)) {
      /* Handle error */
    } else {
      diff = lht - rht;
    }
 
    /* ... */

  }
  mulConsistent((P1,P2),const,no default) -> bool
  divConsistent((P1,P2),const,no default) -> bool
