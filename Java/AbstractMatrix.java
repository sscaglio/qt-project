import java.util.ArrayList;

abstract class AbstractMatrix<T>{
    protected ArrayList<T> matrice;
    protected int righe;
    protected int colonne;

    public AbstractMatrix(ArrayList<T>matrice,int righe,int colonne){
	this.matrice = matrice;
	this.righe = righe;
	this.colonne = colonne;
    }
}
