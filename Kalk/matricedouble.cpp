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

MatriceDouble
MatriceDouble::parse(const QString& rht,unsigned int r,unsigned int c){
    MatriceDouble res = MatriceDouble(r,c);
    if(!(rht == "0")){
        QStringList toBeParsed = rht.split(",",QString::SkipEmptyParts);
        for(unsigned int i = 0; i < r * c;++i){
            res.matrice.push_back(toBeParsed.at(i).toDouble());
        }
    }
    return res;
}

QString
MatriceDouble::convertToQString(const MatriceDouble& rht,const unsigned int r,const unsigned int c){
    QString res = QString();
    if(!rht.matriceNulla()){
        unsigned int i = 0;
        for(; i < (r * c - 1)  ;++i){
            res +=(QString::number(rht.matrice[i]) + ",");
        }
        res+=(QString::number(rht.matrice[i]));
        return res;
    }
    return QString("0");
}
