#include "mainwindow.h"
#include <QApplication>

// libreria limiti (sia per float che per interi)
#include<limits>
#include<iostream>

#include"boundchecker.h"
#include "matrice.h"

using std::numeric_limits;
using std::cout;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Matrice<int> matr1 = Matrice<int>(1,3);
    Matrice<int> matr2 = Matrice<int>(1,3);

    for(int i = 0; i < 3;++i){
        matr1.insertValue(std::numeric_limits<int>::max());
        matr2.insertValue(1);
    }
    Matrice<int> res = Matrice<int>(1,3);
    res = matr1 + matr2;
    res.printAll();
    return a.exec();
}
