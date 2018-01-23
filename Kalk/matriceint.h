#ifndef MATRICEINT_H
#define MATRICEINT_H

#include "matrice.h"

#include "matrixarithmeticexecutor.h"


class MatriceInt : public Matrice<int>
{
    friend class MatrixArithmeticExecutor<MatriceInt,int>;
public:
    MatriceInt(const unsigned int,const unsigned int);

    MatriceInt operator+(const MatriceInt&)const;
    MatriceInt operator-(const MatriceInt&)const;
    MatriceInt operator*(const MatriceInt&)const;

    MatriceInt factorial()const;

    void printAll()const{
        for(unsigned int i= 0 ; i< righe * colonne;++i){
            std::cout << matrice[i] << " ";
        }
    }

    //test fn
    void insertValue(const int& val){
        matrice.push_back(val);
    }
};

#endif // MATRICEINT_H
