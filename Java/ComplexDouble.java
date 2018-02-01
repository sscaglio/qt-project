

public class ComplexDouble
    extends AbstractComplex<Double> implements ArithInterface<ComplexDouble>{
    
    public ComplexDouble(){
	this(1.0);
    }
    
    public ComplexDouble(Double reale){
	this(reale,0.0);
    }
    public ComplexDouble(Double reale,Double immaginaria){
	super(reale,immaginaria);
    }
    
    public ComplexDouble sum(ComplexDouble rht){
	return new ComplexDouble(BoundCheckerDouble.addConsistent(reale,rht.reale),BoundCheckerDouble.addConsistent(immaginaria,rht.immaginaria));
    }

    public ComplexDouble difference(ComplexDouble rht){
	return new ComplexDouble(BoundCheckerDouble.subConsistent(reale,rht.reale),BoundCheckerDouble.subConsistent(immaginaria,rht.immaginaria));
    }
    
    public ComplexDouble product(ComplexDouble rht){
         // prodotto tra 2 complessi descritto da relazione
        // i parte immaginaria()
        //(a + bi)*(c + di) = (ac - bd) + (bc + ad)i
        Double primoTermine = BoundCheckerDouble.mulConsistent(reale,rht.reale);
        Double secondoTermine = BoundCheckerDouble.mulConsistent(immaginaria,rht.immaginaria);
        // ac e bd consistenti
        Double terzoTermine = BoundCheckerDouble.mulConsistent(immaginaria,rht.reale);
        Double quartoTermine = BoundCheckerDouble.mulConsistent(reale,rht.immaginaria);
        // bc e ad consistenti
        Double realeFinale = BoundCheckerDouble.subConsistent(primoTermine,secondoTermine); 
        // ac - bd consistente;
        Double immaginariaFinale = BoundCheckerDouble.addConsistent(terzoTermine,quartoTermine);
        // bc + ad consistente

        // -> (ac - bd) - (bc + ad) consistente
        return new ComplexDouble(realeFinale,immaginariaFinale);
    }

    public ComplexDouble division(ComplexDouble rht){

          // prodotto tra 2 complessi descritto da relazione
        // i parte immaginaria
        //(a + bi)/(c + di) = ((ac - bd)/(c*c + d*d))/((bc + ad)/(c*c + d*d))i
        
        Double primoTermine =BoundCheckerDouble.mulConsistent(reale,rht.reale);
        Double secondoTermine = BoundCheckerDouble.mulConsistent(immaginaria,rht.immaginaria);
        // ac e bd consistenti
        Double terzoTermine =  BoundCheckerDouble.mulConsistent(immaginaria,rht.reale);
        Double quartoTermine =  BoundCheckerDouble.mulConsistent(reale,rht.immaginaria);
        // bc e ad consistenti 
        // ac + bd consistente;
        Double primoNumeratore = BoundCheckerDouble.addConsistent(primoTermine,secondoTermine);;
        // bc - ad consistente
        Double secondoNumeratore = BoundCheckerDouble.subConsistent(terzoTermine,quartoTermine);;
        
        // c al quadrato consistente
        // d al quadrato consistente
        // denominatore consistente
        Double denominatore = BoundCheckerDouble.addConsistent(BoundCheckerDouble.mulConsistent(rht.reale,rht.reale),BoundCheckerDouble.mulConsistent(rht.immaginaria,rht.immaginaria)) ;
        
        // (ac + bd)/(c^2 + d^2) consistente
        Double parteReale = BoundCheckerDouble.divConsistent(primoNumeratore,denominatore);
        // ->((bc - ad)/(c^2 + d^2)) consistente
        Double parteImmaginaria = BoundCheckerDouble.divConsistent(secondoNumeratore,denominatore);;
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
