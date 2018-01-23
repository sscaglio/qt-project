#include "matricedouble.h"

using std::cout;
using std::endl;

MatriceDouble::MatriceDouble(const unsigned int righe,const unsigned int colonne)
    :Matrice(righe,colonne)
{}


MatriceDouble
MatriceDouble::operator +(const MatriceDouble& rht)const{
    return MatrixArithmeticExecutor<MatriceDouble,double>::add(*this,rht);
}

MatriceDouble
MatriceDouble::operator -(const MatriceDouble& rht)const{
    return MatrixArithmeticExecutor<MatriceDouble,double>::sub(*this,rht);
}


MatriceDouble
MatriceDouble::operator *(const MatriceDouble& rht)const{
    return MatrixArithmeticExecutor<MatriceDouble,double>::mul(*this,rht);
}

MatriceDouble
MatriceDouble::squareRoot()const{
    MatriceDouble res = MatriceDouble(righe,colonne);
    for(unsigned int i = 0; i < righe * colonne;++i){
        double resParziale = sqrt(matrice[i]);
        res.matrice.push_back(resParziale);
    }
    return res;
}
