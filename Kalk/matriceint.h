#ifndef MATRICEINT_H
#define MATRICEINT_H

#include "matrice.h"

#include "matrixarithmeticexecutor.h"

#include<QString>
#include<QStringList>

class MatriceInt : public Matrice<int>
{
    friend class MatrixArithmeticExecutor<MatriceInt,int>;
public:
    MatriceInt(const unsigned int = 0,const unsigned int = 0);

    MatriceInt operator+(const MatriceInt&)const;
    MatriceInt operator-(const MatriceInt&)const;
    MatriceInt operator*(const MatriceInt&)const;

    MatriceInt factorial()const;

    //test fn
    void insertValue(const int& val){
        matrice.push_back(val);
    }

    void printAll() const{
        for(unsigned int i = 0 ; i < righe * colonne;++i){
            std::cout << matrice[i] << " ";
        }
    }

    static MatriceInt parse(const QString&,unsigned int,unsigned int);
    static QString convertToQString(const MatriceInt&,const unsigned int ,const unsigned int);
};

#endif // MATRICEINT_H
