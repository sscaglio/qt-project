#include "mainwindow.h"
#include <QApplication>

#include "complessodouble.h"
#include<iostream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    ComplessoDouble x1 = ComplessoDouble(2.5,2.5);
    ComplessoDouble x2 = ComplessoDouble(2.5,2.5);

    (x1 + x2).printAll();
    (x1 - x2).printAll();
    (x1 * x2).printAll();
    (x1 / x2).printAll();
    x1.squareRoot().printAll();

    //ComplessoDouble x3 = ComplessoDouble(5,5);

    return a.exec();
}
