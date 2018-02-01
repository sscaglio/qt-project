import java.util.ArrayList;

public class MatriceDouble
    extends AbstractMatrix<Double>
    implements ArithInterface<MatriceDouble>{
    
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
        
    
    public MatriceDouble sum(MatriceDouble rht){
	MatriceDouble res = new MatriceDouble(righe,colonne);
	for(int i = 0 ; i < (righe * colonne);++i){
	    res.matrice.add(BoundCheckerDouble.addConsistent(matrice.get(i),rht.matrice.get(i)));
	}
	return res;
    }

    public MatriceDouble difference(MatriceDouble rht){
	MatriceDouble res = new MatriceDouble(righe,colonne);
	for(int i = 0 ; i < (righe * colonne);++i){
	    res.matrice.add(BoundCheckerDouble.subConsistent(matrice.get(i),rht.matrice.get(i)));
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
			BoundCheckerDouble.mulConsistent(matrice.get(colonne * i + k),rht.matrice.get(rht.colonne * k + j));
                    risultatoParziale =
			BoundCheckerDouble.addConsistent(risultatoParziale,prodottoParziale);
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


    public static void testMatDouble(){
	MatriceDouble x1 = new MatriceDouble(2,2);
	MatriceDouble x2 = new MatriceDouble(2,2);
	double elt = 0.0;
	for(int i = 0 ; i < (2 * 2);++i){
	    x1.matrice.add(elt);
	    x2.matrice.add(elt);
	    elt = elt + 1.5;
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
	System.out.println("SQUARE ROOT");
	System.out.println(x1.squareRoot());
    }
}
