public class ComplexInt
    extends AbstractComplex<Integer> implements ArithInterface<ComplexInt>{

    Integer upperBound = Integer.MAX_VALUE;
    Integer lowerBound = Integer.MIN_VALUE;
    
    public ComplexInt(){
	this(1);
    }
    
    public ComplexInt(Integer reale){
	this(reale,0);
    }
    public ComplexInt(Integer reale,Integer immaginaria){
	super(reale,immaginaria);
    }


    private Integer addConsistent(Integer lht,Integer rht)
	throws ArithmeticException{
	if((rht > 0) && (lht > (upperBound - rht))){
	    throw new ArithmeticException("integer overflow");
	}
	else if((rht < 0) && (lht < (lowerBound - rht))){
	    throw new ArithmeticException("integer underflow");
	}
	return lht + rht;
    }
	
    private Integer subConsistent(Integer lht,Integer rht)
	throws ArithmeticException{
	if (rht > 0 && (lht < (lowerBound + rht))){
	    throw new ArithmeticException("integer underflow");
	}
	else if((rht < 0) && (lht > (upperBound + rht))){
	    throw new ArithmeticException("integer overflow");
	}
	return lht - rht;
    }

    private Integer mulConsistent(Integer lht,Integer rht){
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
	    if (rht > 0) { /* lht is nonpositive, rht is positive */
		if (lht < (lowerBound / rht)) {
		    throw new ArithmeticException("underflow error in operazione di moltiplcazione, termine sinistro negativo, destro positivo");
		}
	    } else { /* lht and rht are nonpositive */
		if ( (lht != 0) && (rht < (upperBound / lht))) {
		    throw new ArithmeticException("overflow error in operazione di moltiplicazione, termine sinistro e destro negativi");
		}
	    } /* End if lht and rht are nonpositive */
	} /* End if lht is nonpositive */
	return lht * rht;
    }
    

    private Integer divConsistent(Integer rht,Integer lht){
	if (rht == 0){
	    throw new ArithmeticException("divide by zero error in operazione di divisione");
	}
	else if((lht == lowerBound) && (rht == -1)) {
	    throw new ArithmeticException("overflow error in operazione di divisione");
	}
	return lht / rht;
    }

    public ComplexInt sum(ComplexInt rht){
	return new ComplexInt(addConsistent(reale,rht.reale),addConsistent(immaginaria,rht.immaginaria));
    }

    public ComplexInt difference(ComplexInt rht){
	return new ComplexInt(subConsistent(reale,rht.reale),subConsistent(immaginaria,rht.immaginaria));
    }
    
    public ComplexInt product(ComplexInt rht){
         // prodotto tra 2 complessi descritto da relazione
        // i parte immaginaria()
        //(a + bi)*(c + di) = (ac - bd) + (bc + ad)i
        Integer primoTermine = mulConsistent(reale,rht.reale);
        Integer secondoTermine = mulConsistent(immaginaria,rht.immaginaria);
        // ac e bd consistenti
        Integer terzoTermine = mulConsistent(immaginaria,rht.reale);
        Integer quartoTermine = mulConsistent(reale,rht.immaginaria);
        // bc e ad consistenti
        Integer realeFinale = subConsistent(primoTermine,secondoTermine); 
        // ac - bd consistente;
        Integer immaginariaFinale = addConsistent(terzoTermine,quartoTermine);
        // bc + ad consistente

        // -> (ac - bd) - (bc + ad) consistente
        return new ComplexInt(realeFinale,immaginariaFinale);
    }

    public ComplexInt division(ComplexInt rht){

          // prodotto tra 2 complessi descritto da relazione
        // i parte immaginaria
        //(a + bi)/(c + di) = ((ac - bd)/(c*c + d*d))/((bc + ad)/(c*c + d*d))i
        
        Integer primoTermine =mulConsistent(reale,rht.reale);
        Integer secondoTermine = mulConsistent(immaginaria,rht.immaginaria);
        // ac e bd consistenti
        Integer terzoTermine =  mulConsistent(immaginaria,rht.reale);
        Integer quartoTermine =  mulConsistent(reale,rht.immaginaria);
        // bc e ad consistenti 
        // ac + bd consistente;
        Integer primoNumeratore = addConsistent(primoTermine,secondoTermine);;
        // bc - ad consistente
        Integer secondoNumeratore = subConsistent(terzoTermine,quartoTermine);;
        
        // c al quadrato consistente
        // d al quadrato consistente
        // denominatore consistente
        Integer denominatore = addConsistent(mulConsistent(rht.reale,rht.reale),mulConsistent(rht.immaginaria,rht.immaginaria)) ;
        
        // (ac + bd)/(c^2 + d^2) consistente
        Integer parteReale = divConsistent(primoNumeratore,denominatore);
        // ->((bc - ad)/(c^2 + d^2)) consistente
        Integer parteImmaginaria = divConsistent(secondoNumeratore,denominatore);;
        // tutte le operazioni che compongono il risultante complesso sono
        // consistenti -> complesso tornato e' consistente
        return new ComplexInt(parteReale,parteImmaginaria);
     }
    
    public ComplexInt factorial(){
	Integer facReale = reale;
	Integer facImg = immaginaria;

	Integer daMultReal = facReale - 1;
	Integer daMultImg = facImg - 1;

	while(daMultReal > 1){
	    facReale = mulConsistent(facReale,daMultReal);
	    daMultReal = daMultReal - 1;
	}

	while(daMultImg > 1){
	    facImg = mulConsistent(facImg,daMultImg);
	    daMultImg = daMultImg - 1;
	}
	
	return new ComplexInt(facReale,facImg);
    }

     public String toString(){
	String res = new String();
	res+=reale.toString();
	if(immaginaria > 0){
	    res+=(" +");
	}
	return res+=(immaginaria.toString() + "i"); 
    }
    
    public static void testCompInt(){
	ComplexInt x1 = new ComplexInt(6,5);
	ComplexInt x2 = new ComplexInt(3,3);

	
	System.out.println("COMPLESSI DI PARTENZA");
	System.out.println(x1);
	System.out.println(x2);
	
	System.out.println("SOMMA");
	System.out.println(x1.sum(x2));
	System.out.println("DIFFERENZA");
	System.out.println(x1.difference(x2));
	System.out.println("PRODOTTO");
	System.out.println(x1.product(x2));
	System.out.println("FATTORIALE");
	System.out.println(x1.factorial());
    }
}
