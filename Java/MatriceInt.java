import java.util.ArrayList;

public class MatriceInt
    extends AbstractMatrix<Integer>
    implements ArithInterface<MatriceInt>{

    Integer upperBound = Integer.MAX_VALUE;
    Integer lowerBound = Integer.MIN_VALUE;
    
    public MatriceInt(){
	this(1);
    }
    
    public MatriceInt(int righe){
	this(righe,1);
    }

    public MatriceInt(int righe,int colonne){
	this(new ArrayList<Integer>(),righe,colonne);
    }

    public MatriceInt(ArrayList<Integer> matrice,int righe,int colonne){
	super(matrice,righe,colonne);
    }

    public String toString(){
	String res = new String();
	res+=("[");
	int i = 0;
	for(; i < (righe * colonne - 1 );++i){
	    res+=(" " + matrice.get(i) + ",");
	}
	res+=(" " + matrice.get(i) + " ]");
	return res;
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
    
    
    public MatriceInt sum(MatriceInt rht){
	MatriceInt res = new MatriceInt(righe,colonne);
	for(int i = 0 ; i < (righe * colonne);++i){
	    res.matrice.add(addConsistent(matrice.get(i),rht.matrice.get(i)));
	}
	return res;
    }

    public MatriceInt difference(MatriceInt rht){
	MatriceInt res = new MatriceInt(righe,colonne);
	for(int i = 0 ; i < (righe * colonne);++i){
	    res.matrice.add(subConsistent(matrice.get(i),rht.matrice.get(i)));
	}
	return res;
    }

    public MatriceInt product(MatriceInt rht){
	MatriceInt res = new MatriceInt(righe,rht.colonne);
        for(int i = 0 ;i < righe;++i){
            for(int j = 0; j < rht.colonne;++j){
                Integer risultatoParziale = new Integer(0);
                for(int k = 0; k < colonne;++k){
                    Integer prodottoParziale = new Integer(0);
                    prodottoParziale =
			mulConsistent(matrice.get(colonne * i + k),rht.matrice.get(rht.colonne * k + j));
                    risultatoParziale =
			addConsistent(risultatoParziale,prodottoParziale);
                }
                res.matrice.add(risultatoParziale);
            }
        }
        // ogni elemento di matrice risultante e' definito, nessuna eccezione sollevata
        return res;
    }

    public MatriceInt factorial(){
	MatriceInt res = new MatriceInt(righe,colonne);
	for(int i = 0; i < (righe * colonne);++i){
	    Integer factorialParziale = matrice.get(i);
	    Integer daMoltElt = factorialParziale - 1;
	    while(daMoltElt > 1){
		factorialParziale = mulConsistent(factorialParziale,daMoltElt);
		daMoltElt = daMoltElt - 1;
	    }
	    res.matrice.add(factorialParziale);
	}
	return res;
    }
    
    public static void testMatInt(){
	MatriceInt x1 = new MatriceInt(2,2);
	MatriceInt x2 = new MatriceInt(2,2);

	for(int i = 0 ; i < (x1.righe * x1.colonne);++i){
	    x1.matrice.add(i);
	    x2.matrice.add(i);
	}
	System.out.println("MATRICI DI PARTENZA");
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
	    
