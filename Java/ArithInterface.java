
interface ArithInterface<T>{

    public T sum(T rht);
    public T difference(T rht);
    public T product(T rht);

}


interface IntegerSpecificOp<T>{
    public T factorial();
}

interface RealSpecificOp<T>{
    public T sqrt();
}


