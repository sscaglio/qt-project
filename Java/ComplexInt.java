abstract class AbstractComplex<T>{

    protected T reale;
    protected T immaginaria;
    
    public AbstractComplex(T reale,T immaginaria){
	this.reale = reale;
	this.immaginaria = immaginaria;
    }

    public String toString(){
	return new String(reale.toString() + "+" + immaginaria.toString() + "i");
    }
   
}


public class ComplexInt extends AbstractComplex<Integer>{

    public ComplexInt(){
	this(1);
    }
    
    public ComplexInt(Integer reale){
	this(reale,0);
    }
    public ComplexInt(Integer reale,Integer immaginaria){
	super(reale,immaginaria);
    }

    public ComplexInt product(ComplexInt rht){
	return new ComplexInt();
    }

    public ComplexInt factorial(){
	Integer facReale = reale;
	Integer facImg = immaginaria;

	Integer daMultReal = reale - 1;
	Integer daMultImg = immaginaria - 1;

	while(daMultReal > 1){
	    facReale*=daMultReal;
	    daMultReal = daMultReal - 1;
	}

	while(daMultImg > 1){
	    facImg*=daMultImg;
	    daMultImg = daMultImg - 1;
	}
	
	return new ComplexInt(facReale,facImg);
    }

    public static void main(String[] args){
	ComplexInt t1 = new ComplexInt(5,5);
	ComplexInt t2 = new ComplexInt(3,3);

	// // somma
	// System.out.println(t1.sum(t2));

	// // differenza

	// System.out.println(t1.difference(t2));
	
	// // fattoriale
	// System.out.println(t1.factorial());
    }
}
