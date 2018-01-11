#include "mainwindow.h"
#include <QApplication>

// libreria limiti (sia per float che per interi)
#include<limits>

#include"boundchecker.h"


using std::numeric_limits;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Boundchecker<double> provaDouble(numeric_limits<double>::max(),(-1)*(numeric_limits<double>::max()));
    // NB PER VALORI DI TIPO DOUBLE IL MINIMO NEGATIVO E' NEGATIVO DI MAX(PRE C++11)
    provaDouble.testChecker();

Boundchecker<int> provaInt(numeric_limits<int>::max(),(numeric_limits<int>::min()));
  //PER VALORI DI TIPO INT POSSO USARE min come minimo negativo
   provaInt.testChecker();
    return a.exec();
}
