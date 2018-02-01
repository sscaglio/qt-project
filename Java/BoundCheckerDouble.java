public class BoundCheckerDouble{
    static Double upperBound = Double.MAX_VALUE;
    static Double lowerBound = (-1) * Double.MAX_VALUE;

    public static Double addConsistent(Double lht,Double rht) throws ArithmeticException{
	if((rht > 0) && (lht > (upperBound - rht))){
	    throw new ArithmeticException("integer overflow");
	}
	else if((rht < 0) && (lht < (lowerBound - rht))){
	    throw new ArithmeticException("integer underflow");
	}
	return lht + rht;
    }

        public static Double subConsistent(Double lht,Double rht)
	throws ArithmeticException{
	if (rht > 0 && (lht < (lowerBound + rht))){
	    throw new ArithmeticException("integer underflow");
	}
	else if((rht < 0) && (lht > (upperBound + rht))){
	    throw new ArithmeticException("integer overflow");
	}
	return lht - rht;
    }
 
    public static Double mulConsistent(Double lht,Double rht) throws ArithmeticException{
	if (lht > 0) {  /* lht is positive */
	    if (rht > 0) {  /* lht and rht are positive */
		if (lht > (upperBound / rht)) {
		    throw new ArithmeticException("overflow error in operazione di moltiplicazione, termine sinistro e destro positivi");
		}
	    } else { /* lht positive, rht nonpositive */
		if (rht < (lowerBound / lht)) {
		    throw new ArithmeticException("underflow error in operazione di moltiplicazione, termine sinistro positivo, destro negativo");
		}
	    } /* lht positive, rht nonpositive */
	} else { /* lht is nonpositive */
	    if (rht > 0.0) { /* lht is nonpositive, rht is positive */
		if (lht < (lowerBound / rht)) {
		    throw new ArithmeticException("underflow error in operazione di moltiplcazione, termine sinistro negativo, destro positivo");
		}
	    } else { /* lht and rht are nonpositive */
		if ( !(lht.equals(0.0)) && (rht < (upperBound / lht))) {
		    throw new ArithmeticException("overflow error in operazione di moltiplicazione, termine sinistro e destro negativi");
		}
	    } /* End if lht and rht are nonpositive */
	} /* End if lht is nonpositive */
	return lht * rht;
    }
    

    public static Double divConsistent(Double rht,Double lht) throws ArithmeticException{
	if (rht.equals(0)){
	    throw new ArithmeticException("divide by zero error in operazione di divisione");
	}
	else if((lht.equals(lowerBound)) && (rht.equals(-1))) {
	    throw new ArithmeticException("overflow error in operazione di divisione");
	}
	return lht / rht;
    }

    public static void stamp(){
	System.out.println(upperBound);
	System.out.println(lowerBound);
    }

    public static void main(String[] args){
	stamp();
    }
}
