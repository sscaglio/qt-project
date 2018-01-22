#include "mainwindow.h"
#include <QApplication>

#include "complessoint.h"
#include<iostream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    ComplessoInt x1 = ComplessoInt(1,1);
    ComplessoInt x2 = ComplessoInt(1,1);

    (x1 / x2).printAll();

    ComplessoInt x3 = ComplessoInt(5,5);
    x3.factorial().printAll();

    return a.exec();
}
