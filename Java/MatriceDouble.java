import java.util.ArrayList;

public class MatriceDouble
    extends AbstractMatrix<Double>
    implements ArithInterface<MatriceDouble>{

    Double upperBound = Double.MAX_VALUE;
    Double lowerBound = -Double.MAX_VALUE;
    
    public MatriceDouble(){
	this(1);
    }
    
    public MatriceDouble(int righe){
	this(righe,1);
    }

    public MatriceDouble(int righe,int colonne){
	this(new ArrayList<Double>(),righe,colonne);
    }

    public MatriceDouble(ArrayList<Double> matrice,int righe,int colonne){
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
    
    private Double addConsistent(Double lht,Double rht)
	throws ArithmeticException{
	if((rht > 0) && (lht > (upperBound - rht))){
	    throw new ArithmeticException("integer overflow");
	}
	else if((rht < 0) && (lht < (lowerBound - rht))){
	    throw new ArithmeticException("integer underflow");
	}
	return lht + rht;
    }
	
    private Double subConsistent(Double lht,Double rht)
	throws ArithmeticException{
	if (rht > 0 && (lht < (lowerBound + rht))){
	    throw new ArithmeticException("integer underflow");
	}
	else if((rht < 0) && (lht > (upperBound + rht))){
	    throw new ArithmeticException("integer overflow");
	}
	return lht - rht;
    }

    private Double mulConsistent(Double lht,Double rht){
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
    
    
    public MatriceDouble sum(MatriceDouble rht){
	MatriceDouble res = new MatriceDouble(righe,colonne);
	for(int i = 0 ; i < (righe * colonne);++i){
	    res.matrice.add(addConsistent(matrice.get(i),rht.matrice.get(i)));
	}
	return res;
    }

    public MatriceDouble difference(MatriceDouble rht){
	MatriceDouble res = new MatriceDouble(righe,colonne);
	for(int i = 0 ; i < (righe * colonne);++i){
	    res.matrice.add(subConsistent(matrice.get(i),rht.matrice.get(i)));
	}
	return res;
    }

    public MatriceDouble product(MatriceDouble rht){
	MatriceDouble res = new MatriceDouble(righe,rht.colonne);
        for(int i = 0 ;i < righe;++i){
            for(int j = 0; j < rht.colonne;++j){
                Double risultatoParziale = new Double(0);
                for(int k = 0; k < colonne;++k){
                    Double prodottoParziale = new Double(0);
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

    public MatriceDouble squareRoot(){
	
        MatriceDouble res = new MatriceDouble(righe,colonne);
	for(int i = 0 ; i < (righe * colonne);++i){
	    res.matrice.add(Math.sqrt(matrice.get(i)));
	}
	return res;
    }


    public static void main(String[] args){
	MatriceDouble x1 = new MatriceDouble(2,2);
	MatriceDouble x2 = new MatriceDouble(2,2);
	double elt = 0.0;
	for(int i = 0 ; i < (2 * 2);++i){
	    x1.matrice.add(elt);
	    x2.matrice.add(elt);
	    elt = elt + 1.5;
	}

	System.out.println(x1.sum(x2));
	System.out.println(x1.difference(x2));
	System.out.println(x1.product(x2));
	System.out.println(x1.squareRoot());
    }
}
