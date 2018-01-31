public class Use{
    
    public static void main(String[] args){

	System.out.println("INIZIO POLINOMI");
	System.out.println("POLINOMIO A COEFFICIENTI DOUBLE");
	PolinomioDouble.testPolDouble();
       	System.out.println("POLINOMIO A COEFFICIENTI INTERI");
	PolinomioInt.testPolInteri();
	System.out.println("FINE POLINOMI");

	System.out.println("INIZIO MATRICI");
	System.out.println("MATRICE A COEFFICIENTI DOUBLE");
	MatriceDouble.testMatDouble();
       	System.out.println("MATRICE A COEFFICIENTI INTERI");
	MatriceInt.testMatInt();	
	System.out.println("FINE MATRICI");

	System.out.println("INIZIO COMPLESSI");
	System.out.println("COMPLESSI A COEFFICIENTI DOUBLE");
	ComplexDouble.testCompDouble();
       	System.out.println("COMPLESSI A COEFFICIENTI INTERI");
	ComplexInt.testCompInt();	
	System.out.println("FINE COMPLESSI");
    }
}
