#include "mainwindow.h"
#include <QApplication>

#include<iostream>

#include "complessoint.h"
#include "complexviewcalculator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    ComplexViewCalculator<ComplessoInt> x =
            ComplexViewCalculator<ComplessoInt>();
    x.show();
    return a.exec();
}
