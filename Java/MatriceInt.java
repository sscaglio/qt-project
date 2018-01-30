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
	return new MatriceInt();
    }
    
    public static void main(String[] args){
	MatriceInt x1 = new MatriceInt(2,2);
	MatriceInt x2 = new MatriceInt(2,2);

	for(int i = 0 ; i < (x1.righe * x1.colonne);++i){
	    x1.matrice.add(i);
	    x2.matrice.add(i);
	}
	System.out.println(x1.sum(x2));
	System.out.println(x1.difference(x2));
    }
}
	    
