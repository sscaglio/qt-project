public class ArithComplexExecutor<T,U>{

    U upperBound;
    U lowerBound;
    
    public T sumExecutor(T arg1,T arg2){
	return new T(arg1.getReale() + arg2.getReale(),
		     arg1.getImmaginaria() + arg2.getImmaginaria());
    }

    public T differenceExecutor(T arg1,T arg2){
	return new T(arg1.getReale() - arg2.getReale(),
		     arg1.getImmaginaria() - arg2.getImmaginaria());
    }

    public T productExecutor(T arg1,T arg2){
	U parteReale = new U();
	U parteImmaginaria = new U();
	return new T();
    }


}
