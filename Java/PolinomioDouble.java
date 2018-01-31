import java.util.ArrayList;
import java.util.Comparator;
import java.util.Collections;

class MonomioDouble{
    private Double coefficiente;
    private Integer grado;

    public MonomioDouble(){
	this(new Double(0));
    }

    public MonomioDouble(Double coefficiente){
	this(coefficiente,0);
    }

    public MonomioDouble(Double coefficiente,Integer grado){
	this.coefficiente = coefficiente;
	this.grado = grado;
    }

    public Integer getGrado(){
	return grado;
    }

    public Double getCoefficiente(){
	return coefficiente;
    }
}


class MonomioComparator implements Comparator<MonomioDouble>{
    public int compare(MonomioDouble lht,MonomioDouble rht){
	if((lht.getGrado() > rht.getGrado()) ||
	   ((lht.getGrado().equals(rht.getGrado()) && lht.getCoefficiente() > rht.getCoefficiente()))){
	    return 1;
	}
	else if(lht.getGrado().equals(rht.getGrado()) && lht.getCoefficiente().equals(rht.getCoefficiente())){
	    return 0;
	}
	else{
	    return -1;
	}
    }
}

public class PolinomioDouble
    extends AbstractPolynomial<MonomioDouble>
    implements ArithInterface<PolinomioDouble>{

    Double upperBound = Double.MAX_VALUE;
    Double lowerBound = (-1) * Double.MAX_VALUE;

    public PolinomioDouble(){
	super(new ArrayList<MonomioDouble>());
    }

    public String toString(){
	String res = new String();
	int i = 0;
	res+=(polinomio.get(i).getCoefficiente() + " ");
	++i;
	for(; i < polinomio.size();++i){
	    res+=(polinomio.get(i).getCoefficiente() + "x^" + polinomio.get(i).getGrado() + " ");
	}
	return res;
    }
    
    private Integer addConsistent(Integer lht,Integer rht)
	throws ArithmeticException{
	if(rht > 0 && (lht > (upperBound - rht))){
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



    // INIZIO OPERAZIONI CONSISTENZA PER DOUBLE

private Double addConsistent(Double lht,Double rht)
	throws ArithmeticException{
	if(rht > 0 && (lht > (upperBound - rht))){
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


    // FINE OPERAZIONI DI CONSISTENZA PER DOUBLE

    
    
    public PolinomioDouble sum(PolinomioDouble rht){
	int i = 0;
	int j = 0;
	PolinomioDouble res = new PolinomioDouble();
	while(i < polinomio.size() && j < rht.polinomio.size()){
	    if(polinomio.get(i).getGrado().equals(rht.polinomio.get(j).getGrado())){
		//somma consistente tra due monomi
		Double coefficienteRisultante =
		    addConsistent(polinomio.get(i).getCoefficiente(),rht.polinomio.get(j).getCoefficiente());
		if(coefficienteRisultante != 0){
		    res.polinomio.add(new MonomioDouble(coefficienteRisultante,polinomio.get(i).getGrado()));
		}
		++i;
		++j;
	    }
	    else{
		// gradi monomi distinti - > non possibile somma
		if(polinomio.get(i).getGrado() > rht.polinomio.get(j).getGrado()){
		    // grado primo monomio maggiore del secondo
		    res.polinomio.add(polinomio.get(i));
		    ++i;
		}
		else{
		    // grado del secondo monomio maggiore del primo
		    res.polinomio.add(rht.polinomio.get(j));
		    ++j;
		}
	    }
	}
	PolinomioDouble rimanente = new PolinomioDouble();
	if(i < polinomio.size()){
	    // esistono elementi rimanenti nel polinomio sx
	    rimanente.polinomio.addAll(polinomio.subList(i,polinomio.size()));
	}
	if(j < rht.polinomio.size()){
	    // esistono elementi rimanenti nel polinomio dx
	    rimanente.polinomio.addAll(rht.polinomio.subList(j,rht.polinomio.size()));
	}
	if(!(rimanente.polinomio.isEmpty())){
	    // se polinomio rimanente non e' vuoto -> add al termine di res
	    res.polinomio.addAll(rimanente.polinomio);
	}
	return res;
    }
    
    public PolinomioDouble difference(PolinomioDouble rht){
	PolinomioDouble res = new PolinomioDouble();

	int i = 0;
	int j = 0;
	while(i < polinomio.size() && j < rht.polinomio.size()){
            if(polinomio.get(i).getGrado().equals(rht.polinomio.get(j).getGrado())){
                // gradi monomi uguali -> possibile differenza
                //sottrazione consistente tra due monomi
                Double coefficienteRisultante =
		    subConsistent(polinomio.get(i).getCoefficiente(),rht.polinomio.get(j).getCoefficiente());
                if(coefficienteRisultante != 0){
                    res.polinomio.add(new MonomioDouble(coefficienteRisultante,polinomio.get(i).getGrado()));
                }
                ++i;
                ++j;
            }
            else{
                // gradi monomi distinti - > non possibile differenza
                if(polinomio.get(i).getGrado() > rht.polinomio.get(j).getGrado()){
                    // grado primo monomio maggiore del secondo
                    res.polinomio.add(polinomio.get(i));
                    ++i;
                }
                else{
                    // grado del secondo monomio maggiore del primo
                    // appendo negazione (poiche' operando destro di negazione)
                    // a risultato
                    res.polinomio.add(new MonomioDouble((-1) * rht.polinomio.get(j).getCoefficiente(),rht.polinomio.get(j).getGrado()));
                    ++j;
                }
            }
        }
        PolinomioDouble rimanente = new PolinomioDouble();
        if(i < polinomio.size()){
            // esistono elementi rimanenti nel polinomio sx
            rimanente.polinomio.addAll(polinomio.subList(i,polinomio.size()));
        }
        if(j < rht.polinomio.size()){
            // esistono elementi rimanenti nel polinomio dx
            rimanente.polinomio.addAll(rht.polinomio.subList(j,rht.polinomio.size()));
            for(int index = 0 ; index < rimanente.polinomio.size();++index){
                rimanente.polinomio.set(index,new MonomioDouble((-1) * rimanente.polinomio.get(index).getCoefficiente(),rimanente.polinomio.get(index).getGrado()));
            }
        }
        if(!(rimanente.polinomio.isEmpty())){
            // se polinomio rimanente non e' vuoto -> appendi al termine di res
            res.polinomio.addAll(rimanente.polinomio);
        }
        return res;
    }

    public PolinomioDouble product(PolinomioDouble rht){
        PolinomioDouble bufferRes = new PolinomioDouble();
        for(int i= 0; i < polinomio.size();++i){
            // per ogni monomio appartenente a operando sx
            for(int j = 0; j < rht.polinomio.size();++j){
                // per ogni monomio appartenente a operando dx
                // operazione di somma tra gradi e' consistente
                Double coefficienteRisultante =
		    mulConsistent(polinomio.get(i).getCoefficiente(),rht.polinomio.get(j).getCoefficiente());
                if(coefficienteRisultante != 0){
                   
                    // operazione di somma tra gradi e' consistente
                    Integer gradoRisultante = addConsistent(polinomio.get(i).getGrado(),rht.polinomio.get(j).getGrado());
                    bufferRes.polinomio.add(new MonomioDouble(coefficienteRisultante,gradoRisultante));
                }
                // ogni elemento di operando sx e' stato moltiplicato per operando dx
                // e inserito in bufferRes
            }
        }
        Collections.sort(bufferRes.polinomio,new MonomioComparator());
	// bufferRes e' ordinato -> posso semplificare monomi con grado ==
	PolinomioDouble res = new PolinomioDouble();
	int i1 = 0 ;
	while(i1 < bufferRes.polinomio.size()){
            Double coeffGradiUguali = new Double(0);
            // coeffGradiUguali rappresenta coefficiente somma di tutti i
            // monomi di grado ==
            int j1 = i1;

            // i, j  <  bufferRes.polinomio.size()
            while(j1 < bufferRes.polinomio.size() &&
		  bufferRes.polinomio.get(i1).getGrado() == bufferRes.polinomio.get(j1).getGrado()){
		
		// somma consistente tra coefficiente parziale e coefficiente da
		// sommare
		coeffGradiUguali = addConsistent(coeffGradiUguali,bufferRes.polinomio.get(j1).getCoefficiente());
		++j1;
            }
            // monomio puntato da j ha grado diverso rispetto a
            // monomio puntato da i or arrivato a fine di bufferRes
            // coeffGradiUguali contiene somma di tutti i coefficienti
            // di grado uguale a bufferRes.polinomio.get(i)
            res.polinomio.add(new MonomioDouble(coeffGradiUguali,bufferRes.polinomio.get(i1).getGrado()));
            i1 = j1;
            // sposto indice in porzione di lista | grado predecessore < grado attuale
            // i eventualmente ==  bufferRes.polinomio.size() 
	}
	return res;
    }

    public PolinomioDouble squareRoot(){
	PolinomioDouble res = new PolinomioDouble();
	for(int i = 0 ; i < polinomio.size();++i){
	    res.polinomio.add(new MonomioDouble(Math.sqrt(polinomio.get(i).getCoefficiente()),polinomio.get(i).getGrado()));
	}
	return res;
    }
    
    public static void main(String[] args){
	PolinomioDouble x1 = new PolinomioDouble();
	PolinomioDouble x2 = new PolinomioDouble();

	for(int i = 0 ; i < 5;++i){
	    MonomioDouble inserted = new MonomioDouble(new Double(i + 0.5),new Integer(i));
	    x1.polinomio.add(inserted);
	    MonomioDouble inserted2 = new MonomioDouble(new Double(2 * i),new Integer(i));
	    x2.polinomio.add(inserted2);
	}
	System.out.println(x1.sum(x2));
	System.out.println(x1.difference(x2));
	System.out.println(x1.product(x2));
	System.out.println(x1.squareRoot());
    }
}
