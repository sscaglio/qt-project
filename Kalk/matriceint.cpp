#include "matriceint.h"

using std::cout;
using std::endl;

MatriceInt::MatriceInt(const unsigned int righe,const unsigned int colonne)
    :Matrice(righe,colonne)
{}


MatriceInt
MatriceInt::operator +(const MatriceInt& rht)const{
    return MatrixArithmeticExecutor<MatriceInt,int>::add(*this,rht);
}

MatriceInt
MatriceInt::operator -(const MatriceInt& rht)const{
    return MatrixArithmeticExecutor<MatriceInt,int>::sub(*this,rht);
}


MatriceInt
MatriceInt::operator *(const MatriceInt& rht)const{
    return MatrixArithmeticExecutor<MatriceInt,int>::mul(*this,rht);
}

MatriceInt
MatriceInt::factorial()const{

    try{
        MatriceInt risultante = MatriceInt(righe,colonne);
        for(unsigned int i = 0 ; i < (righe * colonne);++i){
            int factorialParziale = matrice[i];
            int daMoltElt = factorialParziale - 1;
            while(daMoltElt > 1){
                bd.mulConsistent(factorialParziale,daMoltElt);
                factorialParziale*=daMoltElt;
                daMoltElt--;
            }
            risultante.matrice.push_back(factorialParziale);
        }
        return risultante;
    }catch(runtime_error &e){
        std::cout << e.what() << std::endl;
    }
    return MatriceInt(0,0);

}


MatriceInt
MatriceInt::parse(const QString & rht,const unsigned int r,const unsigned int c){

    MatriceInt res = MatriceInt(r,c);
    QStringList toBeParsed = rht.split(",",QString::SkipEmptyParts);
    for(unsigned int i = 0; i < r * c;++i){
        res.insertValue(toBeParsed.at(i).toInt());
    }
    return res;
}

QString
MatriceInt::convertToQString(const MatriceInt & rht,const unsigned int r,const unsigned int c){
    QString res = QString();
    unsigned int i = 0;
    for(; i < (r * c - 1)  ;++i){
        res +=(QString::number(rht.matrice[i]) + ",");
    }
    res+=(QString::number(rht.matrice[i]));
    return res;
}
