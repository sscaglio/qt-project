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


    public ComplexInt sum(ComplexInt rht){
	return new ComplexInt(BoundCheckerInt.addConsistent(reale,rht.reale),BoundCheckerInt.addConsistent(immaginaria,rht.immaginaria));
    }

    public ComplexInt difference(ComplexInt rht){
	return new ComplexInt(BoundCheckerInt.subConsistent(reale,rht.reale),BoundCheckerInt.subConsistent(immaginaria,rht.immaginaria));
    }
    
    public ComplexInt product(ComplexInt rht){
	// prodotto tra 2 complessi descritto da relazione
        // i parte immaginaria()
        //(a + bi)*(c + di) = (ac - bd) + (bc + ad)i
        Integer primoTermine = BoundCheckerInt.mulConsistent(reale,rht.reale);
        Integer secondoTermine = BoundCheckerInt.mulConsistent(immaginaria,rht.immaginaria);
        // ac e bd consistenti
        Integer terzoTermine = BoundCheckerInt.mulConsistent(immaginaria,rht.reale);
        Integer quartoTermine = BoundCheckerInt.mulConsistent(reale,rht.immaginaria);
        // bc e ad consistenti
        Integer realeFinale = BoundCheckerInt.subConsistent(primoTermine,secondoTermine); 
        // ac - bd consistente;
        Integer immaginariaFinale = BoundCheckerInt.addConsistent(terzoTermine,quartoTermine);
        // bc + ad consistente

        // -> (ac - bd) - (bc + ad) consistente
        return new ComplexInt(realeFinale,immaginariaFinale);
    }

    public ComplexInt division(ComplexInt rht){

	// prodotto tra 2 complessi descritto da relazione
        // i parte immaginaria
        //(a + bi)/(c + di) = ((ac - bd)/(c*c + d*d))/((bc + ad)/(c*c + d*d))i
        
        Integer primoTermine =BoundCheckerInt.mulConsistent(reale,rht.reale);
        Integer secondoTermine = BoundCheckerInt.mulConsistent(immaginaria,rht.immaginaria);
        // ac e bd consistenti
        Integer terzoTermine =  BoundCheckerInt.mulConsistent(immaginaria,rht.reale);
        Integer quartoTermine =  BoundCheckerInt.mulConsistent(reale,rht.immaginaria);
        // bc e ad consistenti 
        // ac + bd consistente;
        Integer primoNumeratore = BoundCheckerInt.addConsistent(primoTermine,secondoTermine);;
        // bc - ad consistente
        Integer secondoNumeratore = BoundCheckerInt.subConsistent(terzoTermine,quartoTermine);;
        
        // c al quadrato consistente
        // d al quadrato consistente
        // denominatore consistente
	System.out.println(rht.reale +" " +  rht.immaginaria);
        Integer denominatore = BoundCheckerInt.addConsistent(BoundCheckerInt.mulConsistent(rht.reale,rht.reale),BoundCheckerInt.mulConsistent(rht.immaginaria,rht.immaginaria)) ;
        
        // (ac + bd)/(c^2 + d^2) consistente
        Integer parteReale = BoundCheckerInt.divConsistent(primoNumeratore,denominatore);
        // ->((bc - ad)/(c^2 + d^2)) consistente
        Integer parteImmaginaria = BoundCheckerInt.divConsistent(secondoNumeratore,denominatore);
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
	    facReale = BoundCheckerInt.mulConsistent(facReale,daMultReal);
	    daMultReal = daMultReal - 1;
	}

	while(daMultImg > 1){
	    facImg = BoundCheckerInt.mulConsistent(facImg,daMultImg);
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
	ComplexInt x2 = new ComplexInt(4,4);

	
	System.out.println("COMPLESSI DI PARTENZA");
	System.out.println(x1);
	System.out.println(x2);
	
	System.out.println("SOMMA");
	System.out.println(x1.sum(x2));
	System.out.println("DIFFERENZA");
	System.out.println(x1.difference(x2));
	System.out.println("PRODOTTO");
	System.out.println(x1.product(x2));
	System.out.println("DIVISION");
	System.out.println(x1.division(x2));
	System.out.println("FATTORIALE");
	System.out.println(x1.factorial());
    }
}
