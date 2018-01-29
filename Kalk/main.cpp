#include "mainwindow.h"
#include <QApplication>

#include<iostream>

#include "complessoint.h"
#include "complexviewcalculator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
<<<<<<< HEAD
    //MainWindow w;
    //w.show();
    ComplexViewCalculator<ComplessoInt> x =
            ComplexViewCalculator<ComplessoInt>();
    x.show();
=======
    MainWindow w;

    w.show();
>>>>>>> 26c34637398dd4bc3c858118c9f31472f828d3f1
    return a.exec();
}
