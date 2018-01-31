import java.util.ArrayList;

abstract class AbstractPolynomial<T>{

    protected ArrayList<T> polinomio;

    public AbstractPolynomial(ArrayList<T> polinomio){
	this.polinomio = polinomio;
    }
}
