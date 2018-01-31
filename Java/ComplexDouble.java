

public class ComplexDouble
    extends AbstractComplex<Double> implements ArithInterface<ComplexDouble>{

    Double upperBound = Double.MAX_VALUE;
    Double lowerBound = (-1) * Double.MAX_VALUE;
    
    public ComplexDouble(){
	this(1.0);
    }
    
    public ComplexDouble(Double reale){
	this(reale,0.0);
    }
    public ComplexDouble(Double reale,Double immaginaria){
	super(reale,immaginaria);
    }


    private Double addConsistent(Double lht,Double rht)
	throws ArithmeticException{
	if((rht > 0.0) && (lht > (upperBound - rht))){
	    throw new ArithmeticException("integer overflow");
	}
	else if((rht < 0.0) && (lht < (lowerBound - rht))){
	    throw new ArithmeticException("integer underflow");
	}
	return lht + rht;
    }
	
    private Double subConsistent(Double lht,Double rht)
	throws ArithmeticException{
	if (rht > 0.0 && (lht < (lowerBound + rht))){
	    throw new ArithmeticException("integer underflow");
	}
	else if((rht < 0.0) && (lht > (upperBound + rht))){
	    throw new ArithmeticException("integer overflow");
	}
	return lht - rht;
    }

    private Double mulConsistent(Double lht,Double rht){
	if (lht > 0.0) {  /* lht is positive */
	    if (rht > 0.0) {  /* lht and rht are positive */
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
		if ( (lht != 0.0) && (rht < (upperBound / lht))) {
		    throw new ArithmeticException("overflow error in operazione di moltiplicazione, termine sinistro e destro negativi");
		}
	    } /* End if lht and rht are nonpositive */
	} /* End if lht is nonpositive */
	return lht * rht;
    }
    

    private Double divConsistent(Double rht,Double lht){
	if (rht == 0.0){
	    throw new ArithmeticException("divide by zero error in operazione di divisione");
	}
	else if((lht == lowerBound) && (rht == -1)) {
	    throw new ArithmeticException("overflow error in operazione di divisione");
	}
	return lht / rht;
    }

    public ComplexDouble sum(ComplexDouble rht){
	return new ComplexDouble(addConsistent(reale,rht.reale),addConsistent(immaginaria,rht.immaginaria));
    }

    public ComplexDouble difference(ComplexDouble rht){
	return new ComplexDouble(subConsistent(reale,rht.reale),subConsistent(immaginaria,rht.immaginaria));
    }
    
    public ComplexDouble product(ComplexDouble rht){
         // prodotto tra 2 complessi descritto da relazione
        // i parte immaginaria()
        //(a + bi)*(c + di) = (ac - bd) + (bc + ad)i
        Double primoTermine = mulConsistent(reale,rht.reale);
        Double secondoTermine = mulConsistent(immaginaria,rht.immaginaria);
        // ac e bd consistenti
        Double terzoTermine = mulConsistent(immaginaria,rht.reale);
        Double quartoTermine = mulConsistent(reale,rht.immaginaria);
        // bc e ad consistenti
        Double realeFinale = subConsistent(primoTermine,secondoTermine); 
        // ac - bd consistente;
        Double immaginariaFinale = addConsistent(terzoTermine,quartoTermine);
        // bc + ad consistente

        // -> (ac - bd) - (bc + ad) consistente
        return new ComplexDouble(realeFinale,immaginariaFinale);
    }

    public ComplexDouble division(ComplexDouble rht){

          // prodotto tra 2 complessi descritto da relazione
        // i parte immaginaria
        //(a + bi)/(c + di) = ((ac - bd)/(c*c + d*d))/((bc + ad)/(c*c + d*d))i
        
        Double primoTermine =mulConsistent(reale,rht.reale);
        Double secondoTermine = mulConsistent(immaginaria,rht.immaginaria);
        // ac e bd consistenti
        Double terzoTermine =  mulConsistent(immaginaria,rht.reale);
        Double quartoTermine =  mulConsistent(reale,rht.immaginaria);
        // bc e ad consistenti 
        // ac + bd consistente;
        Double primoNumeratore = addConsistent(primoTermine,secondoTermine);;
        // bc - ad consistente
        Double secondoNumeratore = subConsistent(terzoTermine,quartoTermine);;
        
        // c al quadrato consistente
        // d al quadrato consistente
        // denominatore consistente
        Double denominatore = addConsistent(mulConsistent(rht.reale,rht.reale),mulConsistent(rht.immaginaria,rht.immaginaria)) ;
        
        // (ac + bd)/(c^2 + d^2) consistente
        Double parteReale = divConsistent(primoNumeratore,denominatore);
        // ->((bc - ad)/(c^2 + d^2)) consistente
        Double parteImmaginaria = divConsistent(secondoNumeratore,denominatore);;
        // tutte le operazioni che compongono il risultante complesso sono
        // consistenti -> complesso tornato e' consistente
        return new ComplexDouble(parteReale,parteImmaginaria);
     }
    
    public ComplexDouble squareRoot(){
	if(reale < 0.0 || immaginaria < 0.0 ){
	    throw new ArithmeticException("radice di num negativo");
	}
	return new ComplexDouble(Math.sqrt(reale),Math.sqrt(immaginaria));
    }

     public String toString(){
	String res = new String();
	res+=reale.toString();
	if(immaginaria > 0.0){
	    res+=(" +");
	}
	return res+=(immaginaria.toString() + "i"); 
    }
    
    public static void testCompDouble(){
	ComplexDouble x1 = new ComplexDouble(6.5,5.5);
	ComplexDouble x2 = new ComplexDouble(4.0,3.0);

	System.out.println("COMPLESSI DI PARTENZA");
	System.out.println(x1);
	System.out.println(x2);
	
	System.out.println("SOMMA");
	System.out.println(x1.sum(x2));
	System.out.println("DIFFERENZA");
	System.out.println(x1.difference(x2));
	System.out.println("PRODOTTO");
	System.out.println(x1.product(x2));
	System.out.println("SQUARE ROOT");
	System.out.println(x1.squareRoot());    }
}
