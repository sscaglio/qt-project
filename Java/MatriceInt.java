import java.util.ArrayList;

public class MatriceInt
    extends AbstractMatrix<Integer>
    implements ArithInterface<MatriceInt>{
    
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
    
    public MatriceInt sum(MatriceInt rht){
	MatriceInt res = new MatriceInt(righe,colonne);
	for(int i = 0 ; i < (righe * colonne);++i){
	    res.matrice.add(BoundCheckerInt.addConsistent(matrice.get(i),rht.matrice.get(i)));
	}
	return res;
    }

    public MatriceInt difference(MatriceInt rht){
	MatriceInt res = new MatriceInt(righe,colonne);
	for(int i = 0 ; i < (righe * colonne);++i){
	    res.matrice.add(BoundCheckerInt.subConsistent(matrice.get(i),rht.matrice.get(i)));
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
			BoundCheckerInt.mulConsistent(matrice.get(colonne * i + k),rht.matrice.get(rht.colonne * k + j));
                    risultatoParziale =
			BoundCheckerInt.addConsistent(risultatoParziale,prodottoParziale);
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
		factorialParziale = BoundCheckerInt.mulConsistent(factorialParziale,daMoltElt);
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
	    
