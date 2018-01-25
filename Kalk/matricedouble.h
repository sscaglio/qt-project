#ifndef MATRICEDOUBLE_H
#define MATRICEDOUBLE_H

#include "matrice.h"
#include "matrixarithmeticexecutor.h"

#include <math.h>

class MatriceDouble : public Matrice<double>
{
    friend class MatrixArithmeticExecutor<MatriceDouble,double>;

public:
    MatriceDouble(const unsigned int,const unsigned int);

    MatriceDouble operator+(const MatriceDouble&)const;
    MatriceDouble operator-(const MatriceDouble&)const;
    MatriceDouble operator*(const MatriceDouble&)const;

    MatriceDouble squareRoot()const;

    void printAll()const{
        for(unsigned int i= 0 ; i< righe * colonne;++i){
            std::cout << matrice[i] << " ";
        }
    }

    //test fn
    void insertValue(const double& val){
        matrice.push_back(val);
    }
};

#endif // MATRICEDOUBLE_H
